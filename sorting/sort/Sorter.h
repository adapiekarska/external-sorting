#include <fstream>
#include <cmath>
#include <utility>

#include "../Accessors/DataReader.h"
#include "../Accessors/DataWriter.h"
#include "../FileUtilities/FileDisplayer.h"
#include "../Logger/ConsoleLogger.h"

/**
 * Class implementing sorting logic.
 */
class Sorter
{
public:

	Sorter(std::string const & main_file_path, size_t tapes, size_t buffer_size);

	~Sorter();

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
	 * Number of tapes used in distribution phase.
	 */
	size_t tapes;

	/**
	 * Size of the buffer.
	 */
	size_t buffer_size;

	/**
	 * Sorts the input file associated with the Sorter object.
	 */
	void sort(bool step_by_step, bool verbose);

private:

	/**
	 * Instance of the ConsoleLogger associated with the Sorter.
	 */
	ConsoleLogger console_logger;

	/**
	* Sorts the file verbosely.
	*/
	void sort_verbose(bool step_by_step);

	/**
	 * Sorts the file non-verbosely.
	 */
	void sort_non_verbose();

	/**
	 * Distributes series of records from input file accross the tapes. Returns the pair
	 * consisting of number of records and series that were read from the file.
	 */
	std::pair<size_t, size_t> distribute();

	/**
	 * Merges records from the tapes into output file. Returns the number of series
	 * written to the output file.
	 */
	size_t merge();

	/**
	 * Returns the index of the smallest element in the fronts vector that is not associated
	 * with the stopped reader.
	 */
	size_t min_tape_index(std::vector<Int32_Vec> const & fronts, std::vector<bool> & stopped) const;
};