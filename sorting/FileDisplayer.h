#pragma once

#include <iostream>

#include "DataReader.h"

class FileDisplayer
{
public:
	FileDisplayer();
	~FileDisplayer();

	void display(std::string const & file_path);
};

