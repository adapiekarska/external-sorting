#pragma once

#include <fstream>

#include "globals.h"

class DataAccessor
{
public:
	DataAccessor(std::string path);
	~DataAccessor();

	/**
	Gets next record from the file.
	*/
	int32_vec get_next();

private:
	std::ifstream ifs;
	const int BUFFER_SIZE = 5;
	std::vector<int32_vec> buffer;

	/**
	Loads the block of records into the buffer.
	*/
	void load();
};