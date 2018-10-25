#include <iostream>

#include "DataGenerator.h"


int main()
{
	DataGenerator data_generator;
	std::vector<int_vec> data = data_generator.generate(100);

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	system("pause");
	return 0;
}