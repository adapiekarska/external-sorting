#pragma once

#include <fstream>
#include <vector>

#include "DataAccessor.h"
#include "Int32_Vec.h"
#include "globals.h"

class DataWriter : public DataAccessor
{
public:

	unsigned int series;

	DataWriter(std::string const & file_path);
	~DataWriter();

	/**
	Appends the record to the buffer.
	*/
	void put_next(Int32_Vec r);

private:

	std::ofstream ofs;
	Int32_Vec last_put;

	void write_buffer();
};

