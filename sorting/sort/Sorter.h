#include <fstream>

#include "../DataReader.h"
#include "../DataWriter.h"
#include "../FileDisplayer.h"


class Sorter
{
public:

	Sorter(std::string const & main_file_path);
	~Sorter() {};


	/**
	Sorts the input file.
	*/
	void sort();


private:

	std::string main_file_path;
	unsigned int disk_ops;

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of file is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer.
	*/
	void copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of series is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer.
	*/
	void copy_until_eos(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Distributes series of records from input file accross two tapes.
	*/
	void distribute(std::string const &input_file_path);

	/**
	Merges records from the two tapes into output file. Returns the number of series
	written to the output file.
	*/
	unsigned int merge(std::string const &output_file_path);

	/**
	Updates disk operations counter with respect to the readers and writers.
	*/
	void update_disk_ops(std::vector<DataAccessor*> const &accessors);
};