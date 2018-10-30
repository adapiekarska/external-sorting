#pragma once

#include <random>
#include <iostream>
#include <string>
#include <sstream>

#include "Int32_Vec.h"
#include "globals.h"

class DataGenerator
{
public:

	/**
	Generates the vector of size n that contains randomly generated pairs of
	two integers.
	*/
	std::vector<Int32_Vec> random_generate(size_t n, int from, int to) const;

	std::vector<Int32_Vec> user_generate() const;

	DataGenerator() {};
	~DataGenerator() {};
};

