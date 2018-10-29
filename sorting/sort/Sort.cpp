#include "Sort.h"


void Sort::sort(std::string const &input_file_path)
{
	distribute(input_file_path);
	merge(input_file_path);
}

void Sort::copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r)
{
	//writer.put_next(r);
	while (true)
	{
		r = reader.get_next();
		if (reader.eof)
			return;
		writer.put_next(r);
	}
}

void Sort::copy_until_eos(DataReader & reader, DataWriter & writer, Int32_Vec & r)
{
	Int32_Vec prev_r = r;
	//writer.put_next(r);

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

void Sort::merge(std::string const &output_file_path)
{
	// create accessors for tapes
	DataReader tape1_reader("tape1");
	DataReader tape2_reader("tape2");
	DataWriter output_writer(output_file_path);

	Int32_Vec r_t1, r_t2, prev_r_t1, prev_r_t2;
	
	r_t1 = tape1_reader.get_next();
	r_t2 = tape2_reader.get_next();

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
				return;
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
				return;
			}

			if (r_t2 < prev_r_t2)
			{
				// handle end of series on tape 2
				output_writer.put_next(r_t1);
				copy_until_eos(tape1_reader, output_writer, r_t1);
			}

		}
	}
}

void Sort::distribute(std::string const &input_file_path)
{
	// create accessors for tapes
	DataReader input_reader(input_file_path);
	DataWriter tape1_writer("tape1");
	DataWriter tape2_writer("tape2");

	Int32_Vec v1, v2;

	DataWriter* current_writer = &tape1_writer;

	// put the first record onto the first tape
	v1 = input_reader.get_next();
	current_writer->put_next(v1);

	while (true)
	{
		v2 = input_reader.get_next();

		if (input_reader.eof)
			break;

		if (v2 >= v1)
			current_writer->put_next(v2);
		else
		{
			if (current_writer == &tape1_writer)
				current_writer = &tape2_writer;
			else
				current_writer = &tape1_writer;
			current_writer->put_next(v2);
		}
		v1 = v2;
	}
}
