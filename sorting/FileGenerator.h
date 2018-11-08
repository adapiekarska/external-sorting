#pragma once

#include <fstream>
#include <vector>

#include "globals.h"
#include "Int32_Vec.h"


/**
 * Class responsible for generating a binary file on a disk with given content.
 */

class FileGenerator
{
public:

	~FileGenerator() { };

	FileGenerator(std::string path);

	/**
	 * Writes a vector of Int32_Vecs into a binary file. The contents
	 * of a file are written in little endian format.
	 */
	void write(std::vector<Int32_Vec> &v);

private:

	std::string path;

};