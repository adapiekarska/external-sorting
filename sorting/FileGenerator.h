#pragma once

#include <fstream>
#include <vector>

#include "globals.h"
#include "Int32_Vec.h"

class FileGenerator
{
public:

	FileGenerator(std::string path);
	~FileGenerator();

	/**
	Writes a vector of Int32_Vecs into a binary file. The contents
	of a file are written in little endian.
	*/
	void write(std::vector<Int32_Vec> &v);

private:
	std::string path;
};