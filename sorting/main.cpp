#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataAccessor.h"


int main()
{
	DataGenerator data_generator;
	std::vector<int_vec> data = data_generator.generate(100);

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	FileGenerator file_generator("out");
	file_generator.write(data);

	DataAccessor data_accessor("out");

	std::cout << std::endl;
	for (int i = 0; i < 100; i++)
	{
		int_vec next = data_accessor.get_next();
		std::cout << next.first << "  " << next.second << std::endl;
	}
	system("pause");
	return 0;
}