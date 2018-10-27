#pragma once

#include <memory>
#include <random>

#include "Int32_Vec.h"
#include "globals.h"

class DataGenerator
{
public:

	/**
	Generates the vector of size n that contains randomly
	generated pairs of integers representing vectors.
	*/
	std::vector<Int32_Vec> generate(size_t n, int from, int to) const;

	DataGenerator();
	~DataGenerator();
};

