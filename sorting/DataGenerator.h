#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

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

