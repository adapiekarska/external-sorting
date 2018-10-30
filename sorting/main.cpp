#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"
#include "sort/Sorter.h"

int main()
{/*
	DataGenerator data_generator;
	std::vector<Int32_Vec> data = data_generator.generate(8, 0, 10);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	FileGenerator file_generator("data");
	file_generator.write(data);*/
/*
	while (true)
	{
		try
		{
			Int32_Vec next = data_reader.get_next();
			data_writer.put_next(next);
		}
		catch (const EOF_Exception&)
		{
			break;
		}
	}*/

	//DataGenerator dg;
	//std::vector<Int32_Vec> data = dg.user_generate();

	Sorter sorter("data3");
	sorter.sort();

	system("pause");
	return 0;
}