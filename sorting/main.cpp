#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"

int main()
{
	DataGenerator data_generator;
	std::vector<Int32_Vec> data = data_generator.generate(64, 0, 10);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i).first << ", " << data.at(i).second << std::endl;
	}

	FileGenerator file_generator("out");
	file_generator.write(data);

	DataReader data_reader("out");

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

	DataWriter data_writer("data_writer_out");
	data_writer.put_next(Int32_Vec(5, 5));
	data_writer.put_next(Int32_Vec(1, 2));
	data_writer.put_next(Int32_Vec(0, 7));

	system("pause");
	return 0;
}