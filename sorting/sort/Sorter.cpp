#include "Sorter.h"


Sorter::Sorter(std::string const & main_file_path) : disk_ops(0), main_file_path(main_file_path)
{
}

void Sorter::sort(bool step_by_step, bool verbose)
{
	std::string tape1_path = "tape1";
	std::string tape2_path = "tape2";

	FileDisplayer displayer;

	if (verbose || step_by_step)
	{
		std::cout << "Before sort: " << std::endl;
		displayer.display(main_file_path);
		std::cout << std::endl;
	}

	unsigned int series, phase = 0;
	do
	{
		if (verbose || step_by_step)
		{
			std::cout << "PHASE " << phase << std::endl;
		}
		std::vector<std::string> tape_paths = { tape1_path, tape2_path };
		distribute(main_file_path, tape_paths);
		if (verbose || step_by_step)
		{
			std::cout << "Tape 1: ";
			displayer.display(tape1_path);
			std::cout << "Tape 2: ";
			displayer.display(tape2_path);
			std::cout << std::endl;
		}
		series = merge(tape1_path, tape2_path, main_file_path);
		if (verbose || step_by_step)
		{
			std::cout << "Main file: ";
			displayer.display(main_file_path);
			std::cout << std::endl;
		}
		if (step_by_step)
			system("pause");
		if (verbose || step_by_step)
			std::cout << std::endl;
		phase++;
	} while (series > 1);

	if (verbose || step_by_step)
	{
		std::cout << "SORTED." << std::endl;
		std::cout << "After sort: " << std::endl;
		displayer.display(main_file_path);
	}

	std::cout << "Phases: " << phase << std::endl;
	std::cout << "Disk operations: " << disk_ops << std::endl;
}

void Sorter::copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r)
{
	while (true)
	{
		r = reader.get_next();
		if (reader.eof)
			return;
		writer.put_next(r);
	}
}

void Sorter::copy_until_eos(DataReader & reader, DataWriter & writer, Int32_Vec & r)
{
	Int32_Vec prev_r = r;

	while ( true )
	{
		prev_r = r;
		r = reader.get_next();

		if (reader.eof)
			return;

		if (r < prev_r)
			break;

		writer.put_next(r);
	}
}

unsigned int Sorter::merge(std::string const & tape1_path, std::string const & tape2_path, std::string const & output_file_path)
{
	// create accessors for tapes
	DataReader tape1_reader(tape1_path);
	DataReader tape2_reader(tape2_path);
	DataWriter output_writer(output_file_path);

	std::vector<DataAccessor*> accessors = { &tape1_reader, &tape2_reader, &output_writer};

	Int32_Vec r_t1, r_t2, prev_r_t1, prev_r_t2;
	

	// Check whether any of the tapes were empty and copy the other tape
	// entirely into the output file if before were true.
	r_t1 = tape1_reader.get_next();
	if (tape1_reader.eof)
	{
		copy_until_eof(tape2_reader, output_writer, r_t2);
		return output_writer.series;
	}

	r_t2 = tape2_reader.get_next();
	if (tape2_reader.eof)
	{
		output_writer.put_next(r_t1);
		copy_until_eof(tape1_reader, output_writer, r_t1);
		return output_writer.series;
	}

	prev_r_t1 = r_t1;
	prev_r_t2 = r_t2;

	while (true)
	{
		if (r_t1 < r_t2)
		{
			output_writer.put_next(r_t1);
			prev_r_t1 = r_t1;
			r_t1 = tape1_reader.get_next();

			if (tape1_reader.eof)
			{
				// handle end of file on tape 1
				output_writer.put_next(r_t2);
				copy_until_eof(tape2_reader, output_writer, r_t2);
				break;
			}

			if (r_t1 < prev_r_t1)
			{
				// handle end of series on tape 1
				output_writer.put_next(r_t2);
				copy_until_eos(tape2_reader, output_writer, r_t2);
			}
		}
		else
		{
			output_writer.put_next(r_t2);
			prev_r_t2 = r_t2;
			r_t2 = tape2_reader.get_next();

			if (tape2_reader.eof)
			{
				// handle end of file on tape 2
				output_writer.put_next(r_t1);
				copy_until_eof(tape1_reader, output_writer, r_t1);
				break;
			}

			if (r_t2 < prev_r_t2)
			{
				// handle end of series on tape 2
				output_writer.put_next(r_t1);
				copy_until_eos(tape1_reader, output_writer, r_t1);
			}
		}
	}

	update_disk_ops(accessors);
	return output_writer.series;
}

void Sorter::update_disk_ops(std::vector<DataAccessor*> const & accessors)
{
	for (DataAccessor* da : accessors)
		disk_ops += da->disk_ops;
}

void Sorter::distribute(std::string const &input_file_path, unsigned int out_tapes)
{
	// create accessors for tapes
	DataReader input_reader(input_file_path);
	std::vector<DataWriter*> tape_writers;
	std::vector<DataAccessor*> accessors = { &input_reader };

	for (unsigned int i = 0; i < out_tapes; i++)
		tape_writers.push_back(new DataWriter("tape"+i));


	Int32_Vec r1, r2;

	unsigned int current_writer_idx = 0;
	DataWriter* current_writer = tape_writers.at(current_writer_idx);

	// put the first record onto the first tape
	r1 = input_reader.get_next();
	current_writer->put_next(r1);

	while (true)
	{
		r2 = input_reader.get_next();

		if (input_reader.eof)
			break;

		if (r2 >= r1)
			current_writer->put_next(r2);
		else
		{
			current_writer_idx++;
			current_writer_idx %= tape_writers.size();
			current_writer = tape_writers.at(current_writer_idx);
			/*
			if (current_writer == &tape1_writer)
				current_writer = &tape2_writer;
			else
				current_writer = &tape1_writer;*/
			current_writer->put_next(r2);
		}
		r1 = r2;
	}

	update_disk_ops(accessors);
	// TODO UPDATE DISK OPS!!!!!!!
	//update_disk_ops(tape_writers);

	for (std::vector< DataWriter* >::iterator it = tape_writers.begin(); it != tape_writers.end(); ++it)
		delete (*it);
	tape_writers.clear();
}
