#pragma once

#include <fstream>
#include <vector>

#include "../globals.h"
#include "../Int32_Vec.h"


/**
 * Class responsible for generating a binary file on a disc with given content.
 */

class FileGenerator
{
public:

	FileGenerator() { };

	~FileGenerator() { };

	/**
	 * Writes a vector of Int32_Vecs into a binary file with given path. The contents
	 * of a file are written in little endian format.
	 */
	void generate(std::vector<Int32_Vec> &v, std::string const & path);

private:

	std::string path;

};