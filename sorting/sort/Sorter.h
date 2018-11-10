#include <fstream>
#include <iomanip>

#include "../Accessors/DataReader.h"
#include "../Accessors/DataWriter.h"
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
	 * Counter of the disc operations.
	 */
	typedef struct DiscOps
	{
		size_t read;
		size_t write;
	} DiscOps;

	DiscOps disc_ops;

	/**
	 * Path to the file that is to be sorted.
	 */
	std::string main_file_path;

	/**
	* Sorts the file verbosely. Returns the number of phases needed to sort the file.
	*/
	size_t sort_verbose(bool step_by_step, size_t tapes, size_t buffer_size);

	/**
	 * Sorts the file non-verbosely. Returns the number of phases needed to sort the file.
	 */
	size_t sort_non_verbose(size_t tapes, size_t buffer_size);

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

	/**
	 * Uses the FileDisplayer to display the tape's contents.
	 */
	void display_tape_with_name(FileDisplayer & fd, std::string const & tape_path,
		std::string const & tape_name, size_t buffer_size) const;

	/**
	 * Displays sort information.
	 */
	void display_sort_information(size_t tapes, size_t buffer_size, size_t phases, size_t disc_read_ops,
		size_t disc_write_ops) const;
};