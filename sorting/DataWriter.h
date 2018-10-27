#pragma once

#include <fstream>
#include <vector>

#include "Int32_Vec.h"
#include "globals.h"

class DataWriter
{
public:
	DataWriter(std::string path);
	~DataWriter();

	/**
	Appends the record to the buffer.
	*/
	void put_next(Int32_Vec r);

private:

	void write_buffer();

	std::ofstream ofs;
	std::vector<Int32_Vec> buffer;

};

