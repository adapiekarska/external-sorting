#pragma once

#include <fstream>
#include <vector>

#include "Int32_Vec.h"
#include "globals.h"

class DataWriter
{
public:

	unsigned int series;
	unsigned int disk_write_counter;

	DataWriter(std::string path);
	~DataWriter();

	/**
	Appends the record to the buffer.
	*/
	void put_next(Int32_Vec r);

private:

	std::ofstream ofs;
	std::vector<Int32_Vec> buffer;

	Int32_Vec last_put;

	void write_buffer();
};

