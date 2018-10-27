#pragma once

#include <fstream>

#include "globals.h"

class FileGenerator
{
public:
	FileGenerator(std::string path);
	~FileGenerator();

	/**
	Write a vector of int32_vecs into a binary file. The contents
	of a file are written in little endian.
	*/
	void write(std::vector<int32_vec> &v);

private:
	std::string path;
};