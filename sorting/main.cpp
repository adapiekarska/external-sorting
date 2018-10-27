#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataAccessor.h"


int main()
{
	DataGenerator data_generator;
	std::vector<int32_vec> data = data_generator.generate(1, 0, 10);

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	FileGenerator file_generator("out");
	file_generator.write(data);

	DataAccessor data_accessor("out");

	std::cout << std::endl;

	while (true)
	{
		try
		{
			int32_vec next = data_accessor.get_next();
			std::cout << next.first << "  " << next.second << std::endl;
		}
		catch (const EOF_Exception&)
		{
			break;
		}
	}

	system("pause");
	return 0;
}