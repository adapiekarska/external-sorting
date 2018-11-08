#include "DataGenerator.h"


std::vector<Int32_Vec> DataGenerator::random_generate(size_t n, int from, int to) const
{
	std::vector<Int32_Vec> data;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(from, to);

	while (n--)
		data.push_back(Int32_Vec(distr(eng), distr(eng)));

	return data;
}

std::vector<Int32_Vec> DataGenerator::user_generate() const
{
	std::vector<Int32_Vec> data;

	std::cout << "Please provide space-separated pairs of integers." << std::endl;

	std::string line;

	int32_t first, second;
	
	do
	{
		std::getline(std::cin, line);
		std::istringstream iss(line);
		if (iss >> first >> second)
			data.push_back(Int32_Vec(first, second));
	} while (line != "");

	return data;
}
