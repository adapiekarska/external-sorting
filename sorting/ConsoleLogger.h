#pragma once

#include <iostream>

#include "FileDisplayer.h"

class Sorter;

/**
 * Class responsible for logging output information on the console.
 */
class ConsoleLogger
{
public:

	//ConsoleLogger(std::string const & input_file_path, size_t tapes, size_t buffer_size);
	
	ConsoleLogger(Sorter*);

	~ConsoleLogger();

	/**
	 * Logs information after i-th phase.
	 */
	void log_after_phase(size_t i);

	/**
	 * Logs information about initial state of the file.
	 */
	void log_initial_state();

	/**
	 * Logs information about the final state of the file.
	 */
	void log_final_state();

	/**
	* Displays sort information.
	*/
	void log_sorting_information(size_t phases) const;

private:

	FileDisplayer file_displayer;
	
	/**
	 * Following fields do not change during the time of the sort,
	 * therefore they are stored in the logger.
	 */
	//std::string input_file_name;
	//size_t tapes;
	//size_t buffer_size;

	Sorter* sorter;

	/**
	 * Number of characters on which the name of each tape is to be displayed.
	 */
	size_t name_display_width;

	/**
	* Displays the tape's contents.
	*/
	void log_tape_with_name(std::string const & tape_path,
		std::string const & tape_name);

};

