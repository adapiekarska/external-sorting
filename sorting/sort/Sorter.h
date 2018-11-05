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
	Sorts the input file associated with the Sorter object.
	*/
	void sort(bool step_by_step, bool verbose, size_t tapes);


private:

	/**
	Path to the file that is to be sorted.
	*/
	std::string main_file_path;

	/**
	Number of tapes to distribute over.
	*/
	size_t tapes;

	/**
	Counter of the disk operations.
	*/
	size_t disk_ops;

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of file is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer. The value referenced
	by r at the moment of calling the function will NOT be copied to the writer's
	tape.
	*/
	void copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Distributes series of records from input file accross the tapes.
	*/
	void distribute(std::string const & input_file_path);

	/**
	Merges records from the tapes into output file. Returns the number of series
	written to the output file.
	*/
	size_t merge(std::string const &output_file_path);

	/**
	Returns the index of the smallest element in the fronts vector that is not associated
	with the stopped reader.
	*/
	size_t min(std::vector<Int32_Vec> const & fronts, std::vector<bool> & stopped) const;

	void update_disk_ops(std::vector<DataAccessor*> accessors);
};