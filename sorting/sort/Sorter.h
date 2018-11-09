#include <fstream>

#include "../DataReader.h"
#include "../DataWriter.h"
#include "../FileDisplayer.h"

/**
 * Class implementing sorting logic.
 */
class Sorter
{
public:

	Sorter(std::string const & main_file_path);

	~Sorter() { };

	/**
	 * Sorts the input file associated with the Sorter object.
	 */
	void sort(bool step_by_step, bool verbose, size_t tapes, size_t buffer_size);

private:

	/**
	 * Path to the file that is to be sorted.
	 */
	std::string main_file_path;

	/**
	 * Counter of the disc read operations.
	 */
	size_t disc_read_ops;

	/**
	 * Counter of the disc write operations.
	 */
	size_t disc_write_ops;

	/**
	 * Distributes series of records from input file accross the tapes.
	 */
	void distribute(size_t tapes, size_t buffer_size);

	/**
	 * Merges records from the tapes into output file. Returns the number of series
	 * written to the output file.
	 */
	size_t merge(size_t tapes, size_t buffer_size);

	/**
	 * Returns the index of the smallest element in the fronts vector that is not associated
	 * with the stopped reader.
	 */
	size_t min_tape_index(std::vector<Int32_Vec> const & fronts, std::vector<bool> & stopped) const;

};