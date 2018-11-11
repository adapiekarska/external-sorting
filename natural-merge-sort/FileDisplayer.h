#pragma once

#include <iostream>

#include "DataReader.h"


/**
 * Class that is responsible for graphically displaying the contents of
 * the binary file in a user-friendly way. The class uses the DataReader's
 * functionality of block-read.
 */

class FileDisplayer
{
public:

	FileDisplayer() {};

	~FileDisplayer() {};

	/**
	 * Displays contents of the file. Uses DataReader object and
	 * utilizes its ability of block read.
	 */
	void display(std::string const & file_path, size_t buffer_size);
};

