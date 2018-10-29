#include <fstream>

#include "../DataReader.h"
#include "../DataWriter.h"
#include "../FileDisplayer.h"

class Sort
{
public:

	/**
	Sorts the input file.
	*/
	static void sort(std::string const &input_file_path);

	

private:

	/**
	Disable the creation of a class.
	*/
	Sort() {};
	~Sort() {};

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of file is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer.
	*/
	static void copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of series is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer.
	*/
	static void copy_until_eos(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Distributes series of records from input file accross two tapes.
	*/
	static void distribute(std::string const &input_file_path);

	/**
	Merges records from the two tapes into output file.
	*/
	static void merge(std::string const &output_file_path);
};