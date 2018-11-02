#include "Sorter.h"


Sorter::Sorter(std::string const & main_file_path) : disk_ops(0), main_file_path(main_file_path)
{
}

void Sorter::sort(bool step_by_step, bool verbose)
{
	std::string tape1_path = "tape0";
	std::string tape2_path = "tape1";

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
		distribute(main_file_path, 2);
		if (verbose || step_by_step)
		{
			std::cout << "Tape 1: ";
			displayer.display(tape1_path);
			std::cout << "Tape 2: ";
			displayer.display(tape2_path);
			std::cout << std::endl;
		}
		series = merge(main_file_path, 2);
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

void Sorter::copy(std::vector<DataReader*>& readers, DataWriter & writer)
{
}

unsigned int Sorter::merge(std::string const & output_file_path, unsigned int in_tapes)
{
	// create accessors for tapes
	//DataReader tape1_reader(tape1_path);
	//DataReader tape2_reader(tape2_path);
	
	std::vector<DataReader*> tape_readers;
	for (unsigned int i = 0; i < in_tapes; i++)
		tape_readers.push_back(new DataReader("tape" + std::to_string(i)));

	DataWriter output_writer(output_file_path);

	// std::vector<DataAccessor*> accessors = { &tape1_reader, &tape2_reader, &output_writer};

	std::vector<Int32_Vec> fronts;
	std::vector<Int32_Vec> prev_fronts;
	
	Int32_Vec record;

	// Get first records from all tapes and check whether any of the tapes
	// is empty
	for (std::vector<DataReader*>::iterator it = tape_readers.begin(); it != tape_readers.end();)
	{
		DataReader* reader = *it;
		record = reader->get_next();
		if (reader->eof)
		{
			it = tape_readers.erase(it);
		}
		else
		{
			fronts.push_back(record);
			it++;
		}
	}

	for (size_t i = 0; i < fronts.size(); i++)
		prev_fronts.push_back(fronts.at(i));
	
	unsigned int idx;
	DataReader* current_reader;
	while (true)
	{
		idx = min(fronts);
		output_writer.put_next(fronts.at(idx));

		current_reader = tape_readers.at(idx);
		record = current_reader->get_next();
		if (current_reader->eof)
		{
			tape_readers.erase(tape_readers.begin() + idx);
			fronts.erase(fronts.begin() + idx);
			prev_fronts.erase(prev_fronts.begin() + idx);
		}
		else
		{
			if (fronts.at(idx) < prev_fronts.at(idx))
			{
				// end of series on tape with index idx

			}
			prev_fronts.at(idx) = fronts.at(idx);
			fronts.at(idx) = record;
		}
		// exit the loop if all of the readers are exhausted
		if (tape_readers.empty())
			break;
	}

	//while (true)
	//{
	//	if (r_t1 < r_t2)
	//	{
	//		output_writer.put_next(r_t1);
	//		prev_r_t1 = r_t1;
	//		r_t1 = tape1_reader.get_next();

	//		if (tape1_reader.eof)
	//		{
	//			// handle end of file on tape 1
	//			output_writer.put_next(r_t2);
	//			copy_until_eof(tape2_reader, output_writer, r_t2);
	//			break;
	//		}

	//		if (r_t1 < prev_r_t1)
	//		{
	//			// handle end of series on tape 1
	//			output_writer.put_next(r_t2);
	//			copy_until_eos(tape2_reader, output_writer, r_t2);
	//		}
	//	}
	//	else
	//	{
	//		output_writer.put_next(r_t2);
	//		prev_r_t2 = r_t2;
	//		r_t2 = tape2_reader.get_next();

	//		if (tape2_reader.eof)
	//		{
	//			// handle end of file on tape 2
	//			output_writer.put_next(r_t1);
	//			copy_until_eof(tape1_reader, output_writer, r_t1);
	//			break;
	//		}

	//		if (r_t2 < prev_r_t2)
	//		{
	//			// handle end of series on tape 2
	//			output_writer.put_next(r_t1);
	//			copy_until_eos(tape1_reader, output_writer, r_t1);
	//		}
	//	}
	//}

	// TODO update disk ops
	//update_disk_ops(accessors);

	for (std::vector< DataReader* >::iterator it = tape_readers.begin(); it != tape_readers.end(); ++it)
		delete (*it);
	tape_readers.clear();

	return output_writer.series;
}

void Sorter::distribute(std::string const &input_file_path, unsigned int out_tapes)
{
	// create accessors for tapes
	DataReader input_reader(input_file_path);
	std::vector<DataWriter*> tape_writers;
	//std::vector<DataAccessor*> accessors = { &input_reader };

	for (unsigned int i = 0; i < out_tapes; i++)
		tape_writers.push_back(new DataWriter("tape"+std::to_string(i)));


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

	//update_disk_ops(accessors);
	// TODO UPDATE DISK OPS!!!!!!!
	//update_disk_ops(tape_writers);

	for (std::vector< DataWriter* >::iterator it = tape_writers.begin(); it != tape_writers.end(); ++it)
		delete (*it);
	tape_writers.clear();
}

void Sorter::update_disk_ops(std::vector<DataAccessor*> const & accessors)
{
	for (DataAccessor* da : accessors)
		disk_ops += da->disk_ops;
}

unsigned int Sorter::min(std::vector<Int32_Vec> const & vec) const
{
	unsigned int min = 0;
	for (size_t i=1; i<vec.size(); i++)
		if (vec.at(i) < vec.at(min))
			min = i;

	return min;
}
