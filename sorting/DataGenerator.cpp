#include "DataGenerator.h"



std::vector<int32_vec> DataGenerator::generate(size_t n, int from, int to) const
{
	std::vector<int32_vec> data;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(from, to);

	while (n--)
	{
		data.push_back(int32_vec(distr(eng), distr(eng)));
	}

	return data;
}

DataGenerator::DataGenerator()
{
}


DataGenerator::~DataGenerator()
{
}
