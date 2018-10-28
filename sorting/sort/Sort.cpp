#include "Sort.h"


void Sort::sort(std::string const &input_file_path)
{
	distribute(input_file_path);
	merge(input_file_path);
}

void Sort::merge(std::string const &output_file_path)
{
	// create accessors for tapes
	DataReader tape1_reader("tape1");
	DataReader tape2_reader("tape2");
	DataWriter output_writer(output_file_path);

	Int32_Vec v_t1, v_t2, prev_v_t1, prev_v_t2;
	
	v_t1 = tape1_reader.get_next();
	v_t2 = tape2_reader.get_next();

	while (true)
	{
		if (v_t1 < v_t2)
		{
			try
			{
				output_writer.put_next(v_t1);
				v_t1 = tape1_reader.get_next();
			}
			catch (const EOF_Exception&)
			{
				while (true)
				{
					try
					{
						v_t2 = tape2_reader.get_next();
						output_writer.put_next(v_t2);
					}
					catch (const EOF_Exception&)
					{
						output_writer.put_next(v_t2);
						return;
					}
				}
			}
		}
		else
		{
			try
			{
				output_writer.put_next(v_t2);
				v_t2 = tape2_reader.get_next();
			}
			catch (const EOF_Exception&)
			{
				output_writer.put_next(v_t2);
				while (true)
				{
					try
					{
						v_t1 = tape1_reader.get_next();
						output_writer.put_next(v_t1);
					}
					catch (const EOF_Exception&)
					{
						output_writer.put_next(v_t1);
						return;
					}
				}
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
		try
		{
			v2 = input_reader.get_next();
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
		catch (const EOF_Exception&)
		{
			break;
		}
	}
}
