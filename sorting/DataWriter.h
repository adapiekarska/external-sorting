#pragma once

#include <fstream>
#include <vector>

#include "DataAccessor.h"
#include "Int32_Vec.h"
#include "globals.h"

class DataWriter : public DataAccessor
{
public:

	/**
	Series counter
	*/
	unsigned int series;

	DataWriter(std::string const & file_path);
	~DataWriter();

	/**
	Appends the record r to the buffer. If the buffer is full,
	block write to the file is performed.
	*/
	void put_next(Int32_Vec r);

private:

	std::ofstream ofs;
	Int32_Vec last_put;

	/**
	Writes buffer to the file.
	*/
	void write_buffer();
};

