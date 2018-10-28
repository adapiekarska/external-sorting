#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"
#include "sort/Sort.h"

int main()
{
	DataGenerator data_generator;
	std::vector<Int32_Vec> data = data_generator.generate(64, 0, 10);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	FileGenerator file_generator("data");
	file_generator.write(data);

	/*DataReader data_reader("data");

	std::cout << std::endl;

	while (true)
	{
		try
		{
			Int32_Vec next = data_reader.get_next();
			std::cout << next.first << "  " << next.second << std::endl;
		}
		catch (const EOF_Exception&)
		{
			break;
		}
	}
*/

	Sort::sort("data");

	system("pause");
	return 0;
}