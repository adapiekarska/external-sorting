#include <fstream>

#include "../DataReader.h"
#include "../DataWriter.h"


class Sort
{
public:
	Sort();
	~Sort();

	/**
	Sorts the input file.
	*/
	static void sort(std::string const &input_file_path);

private:

	/**
	Distributes series of records from input file accross two tapes.
	*/
	static void distribute(std::string const &input_file_path);
};