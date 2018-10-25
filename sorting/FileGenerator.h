#pragma once

#include <fstream>

#include "globals.h"

class FileGenerator
{
public:
	FileGenerator(std::string path);
	~FileGenerator();

	void write(std::vector<int_vec> const &v);

private:
	std::ofstream ofs;
};