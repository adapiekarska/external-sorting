#include <fstream>

#include "../DataReader.h"
#include "../DataWriter.h"


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
	Distributes series of records from input file accross two tapes.
	*/
	static void distribute(std::string const &input_file_path);

	/**
	Merges records from the two tapes into output file.
	*/
	static void merge(std::string const &output_file_path);
};