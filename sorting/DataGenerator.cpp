#include "DataGenerator.h"



std::vector<int_vec> DataGenerator::generate(size_t n) const
{
	std::vector<int_vec> data;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(MIN_VAL, MAX_VAL);

	while (n--)
	{
		data.push_back(int_vec(distr(eng), distr(eng)));
	}

	return data;
}

DataGenerator::DataGenerator()
{
}


DataGenerator::~DataGenerator()
{
}
