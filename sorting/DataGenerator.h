#pragma once

#include <vector>
#include <memory>
#include <random>

#define MAX_VAL 2147483647

typedef std::pair<int, int> int_vec;


class DataGenerator
{
public:

	/**
	Generates the vector of size n that contains randomly
	generated pairs of integers.
	*/
	std::vector<int_vec> generate(size_t n);

	DataGenerator();
	~DataGenerator();
};

