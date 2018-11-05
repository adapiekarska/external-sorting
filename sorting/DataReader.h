#pragma once

#include <fstream>
#include <vector>

#include "DataAccessor.h"
#include "Int32_Vec.h"
#include "globals.h"

class DataReader : public DataAccessor
{
public:

	/**
	Flag indicating whether the end of file has been reached. Note that
	this is set only after the file reader has gone past the end of file,
	not when the last byte is reached.
	*/
	bool eof;

	/**
	Flag indicating whether the end of series has been reached.
	*/
	bool eos;

	/**
	Constructors and destructors.
	*/
	DataReader(std::string const & file_path);
	~DataReader();

	/**
	Gets next record from the file.
	*/
	Int32_Vec get_next();

private:
	std::ifstream ifs;

	Int32_Vec last_read;

	/**
	Loads the block of records into the buffer.
	Returns number of the records loaded, which should be
	equal to BUFFER_SIZE except the situation when there is
	less than BUFFER_SIZE records left to read until EOF.
	*/
	size_t load_buffer();

};

