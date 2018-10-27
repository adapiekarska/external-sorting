#pragma once

#include <fstream>
#include <vector>

#include "Int32_Vec.h"
#include "exceptions\EOF_Exception.h"
#include "globals.h"

class DataReader
{
public:
	DataReader(std::string path);
	~DataReader();

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

