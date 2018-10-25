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
	int_vec get_next();

private:
	std::ifstream ifs;
	const int BUFFER_SIZE = 5;
	std::vector<int_vec> buffer;

	void load();
};