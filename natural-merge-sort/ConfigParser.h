#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>

#include "globals.h"

class ConfigParser
{
public:

	/**
	 * Enum type with all possible input modes.
	 */
	enum input_mode
	{
		NONE,			// initial state
		IN_RANDOM,		// randomly generated file
		IN_FILE,		// input file from disk
		IN_USER			// user generated records
	};

	ConfigParser() { };
	
	~ConfigParser() { };

	void parse_arguments(int argc, char** argv);

	bool get_step_by_step();

	bool get_verbose();

	size_t get_buffer_size();

	size_t get_tapes();

	input_mode get_i_mode();

	size_t get_records();

	int get_min_range();

	int get_max_range();

	std::string get_input_file_path();

private:

	/**
	* Flag indicating whether the sort should be performed step-by-step.
	*/
	bool step_by_step;

	/**
	* Level of verbosity. False - none, true - full.
	*/
	bool verbose;

	/**
	* Size of the buffer used in block read/write operations.
	*/
	size_t buffer_size;

	/**
	* Number of tapes used in the distribution phase of the sort.
	*/
	size_t tapes;

	/**
	* Input mode.
	*/
	input_mode i_mode;

	/**
	* Number of records, if randomised generating was chosen.
	*/
	size_t records;

	/**
	* Lower bound for values of randomised records.
	*/
	int min_range;

	/**
	* Upper bound for values of randomised records.
	*/
	int max_range;

	/**
	* Path to the input file path, if file input was chosen.
	*/
	std::string input_file_path;
};

