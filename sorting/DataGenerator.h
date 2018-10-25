#pragma once

#include <memory>
#include <random>

#include "globals.h"

class DataGenerator
{
public:

	/**
	Generates the vector of size n that contains randomly
	generated pairs of integers.
	*/
	std::vector<int_vec> generate(size_t n) const;

	DataGenerator();
	~DataGenerator();

private:
	const int MIN_VAL = 0;
	const int MAX_VAL = 10; //2147483647;
};

