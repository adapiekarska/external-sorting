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
	void sort(bool step_by_step, bool verbose);


private:

	std::string main_file_path;
	unsigned int disk_ops;

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of file is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer. The value referenced
	by r at the moment of calling the function will NOT be copied to the writer's
	tape.
	*/
	void copy_until_eof(DataReader & reader, DataWriter & writer, Int32_Vec &r);

	/**
	Copies records from the tape associated with reader to the tape associated with
	writer until the end of series is reached. Note that r must be a reference to
	the record that was last put in the data writer's buffer. The value referenced
	by r at the moment of calling the function will NOT be copied to the writer's
	tape.
	*/
	void copy_until_eos(DataReader & reader, DataWriter & writer, Int32_Vec & r);

	void copy(std::vector<DataReader*>& readers, DataWriter & writer,
		std::vector<Int32_Vec> & fronts, std::vector<Int32_Vec> & prev_fronts);

	/**
	Distributes series of records from input file accross the tapes.
	*/
	void distribute(std::string const & input_file_path, unsigned int out_tapes);

	/**
	Merges records from the two tapes into output file. Returns the number of series
	written to the output file.
	*/
	unsigned int merge(std::string const &output_file_path, unsigned int in_tapes);

	/**
	Updates disk operations counter with respect to the readers and writers.
	*/
	void update_disk_ops(std::vector<DataAccessor*> const &accessors);

	unsigned int min(std::vector<Int32_Vec> const & vec) const;
};