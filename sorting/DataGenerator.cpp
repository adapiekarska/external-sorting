#include "DataGenerator.h"



std::vector<int_vec> DataGenerator::generate(size_t n)
{
	std::vector<int_vec> data;

	srand(time(NULL));
	while (n--)
	{
		data.push_back(int_vec(rand(), rand()));
	}

	return data;
}

DataGenerator::DataGenerator()
{
}


DataGenerator::~DataGenerator()
{
}
