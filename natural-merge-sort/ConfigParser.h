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

	bool step_by_step;
	
	bool verbose;
	
	size_t buffer_size;
	
	size_t tapes;

	input_mode input_mode;

	size_t records;
	
	std::string input_file_path;

	ConfigParser() { };
	
	~ConfigParser() { };

	void parse_arguments(int argc, char** argv);

};

