#pragma once

#include <fstream>
#include <stdexcept>
#include <vector>

#include "globals.h"
#include "exceptions/EOF_Exception.h"
#include "Int32_Vec.h"

class DataAccessor
{
public:
	DataAccessor(std::string path);
	~DataAccessor();

	/**
	Gets next record from the file. Throws an EOF exception
	if there is no next record to be read.
	*/
	Int32_Vec get_next();

private:
	std::ifstream ifs;
	std::vector<Int32_Vec> buffer;

	/**
	Loads the block of records into the buffer.
	Returns number of the records loaded, which should be
	equal to BUFFER_SIZE except the situation when there is
	less than BUFFER_SIZE records left to read until EOF.
	*/
	unsigned int load();
};