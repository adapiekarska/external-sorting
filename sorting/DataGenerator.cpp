#include "DataGenerator.h"


std::vector<Int32_Vec> DataGenerator::generate(size_t n, int from, int to) const
{
	std::vector<Int32_Vec> data;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(from, to);

	while (n--)
	{
		data.push_back(Int32_Vec(distr(eng), distr(eng)));
	}

	return data;
}

DataGenerator::DataGenerator()
{
}


DataGenerator::~DataGenerator()
{
}
