#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"
#include "sort/Sorter.h"

enum input_mode
{
	NONE = -1,
	IN_FILE = 0,
	IN_USER = 1
};

typedef struct CONFIG
{
	bool valid;
	bool step_by_step;
	input_mode input_mode;
	std::string input_file_path;
} CONFIG;

CONFIG parse_args(int argc, char** argv)
{
	CONFIG config;
	config.valid = true;
	config.step_by_step = false;
	config.input_mode = NONE;
	config.input_file_path = "";

	if (argc == 0)
		config.valid = false;

	std::vector<std::string> opts;
	for (int i = 1; i < argc; ++i)
		opts.push_back(argv[i]);

	unsigned int i = 0;
	while (i < opts.size())
	{
		if (!config.valid)
			break;
		std::string opt = opts[i];
		if (opt == "-s" || opt == "--step-by-step")
		{
			config.step_by_step = true;
		}
		else if ((opt == "-f" || opt == "--file"))
		{
			if (i != opts.size() - 1)
			{
				if (config.input_mode == IN_USER)
				{
					std::cout << "Invalid option " << opt << " if -u specified before." << std::endl;
					config.valid = false;
				}
				else
				{
					// omit the file path in argument parsing
					config.input_mode = input_mode::IN_FILE;
					if (opts[i + 1][0] != '-')
					{
						config.input_file_path = opts[i + 1];
						i++;
					}
					else
					{
						std::cout << "Missing filename after " << opt << std::endl;
						config.valid = false;
					}
				}
			}
			else
			{
				config.valid = false;
			}
		}
		else if (opt == "-u" || opt == "--user")
		{
			if (config.input_mode == input_mode::IN_FILE)
			{
				std::cout << "Invalid option " << opt << " if -f specified before." << std::endl;
				config.valid = false;
			}
			else
			{
				config.input_mode = IN_USER;
			}
		}
		else if (opt == "-h" || opt == "--help")
		{

		}
		else
		{
			std::cout << "Unknown option " << opt << std::endl;
			config.valid = false;
		}
		i++;
	}
	return config;
}

int main(int argc, char** argv)
{
	CONFIG config = parse_args(argc, argv);
	std::cout << "valid: " << config.valid << std::endl;
	std::cout << "input_mode" << config.input_mode << std::endl;
	std::cout << "step by step" << config.step_by_step << std::endl;
	std::cout << "input file path" << config.input_file_path << std::endl;

	/*
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

	//DataWriter dwriter("data4");
	//std::vector<int32_t> v = { 44, 55, 12, 42, 94, 18, 6, 67, 45, 148, 356, 7, 1 };

	//for (int32_t i : v)
	//	dwriter.put_next(Int32_Vec(i, i));

	Sorter sorter("data5");
	sorter.sort();

	system("pause");
	return 0;
}