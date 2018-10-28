#include "Sort.h"


Sort::Sort()
{
}

Sort::~Sort()
{
}

void Sort::sort(std::string const &input_file_path)
{
	distribute(input_file_path);
}

void merge()
{

}

void Sort::distribute(std::string const &input_file_path)
{

	std::ofstream tape1("tape1", std::ios::binary);
	std::ofstream tape2("tape2", std::ios::binary);

	// create accessors for tapess
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

	tape1.close();
	tape2.close();
}
