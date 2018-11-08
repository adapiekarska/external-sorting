#pragma once

#include <iostream>

#include "DataReader.h"

class FileDisplayer
{
public:

	FileDisplayer() {};

	~FileDisplayer() {};

	/**
	Displays contents of the file. Uses DataReader object and
	utilizes its ability of block read.
	*/
	void display(std::string const & file_path, size_t buffer_size);
};

