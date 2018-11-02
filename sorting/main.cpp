#include <iostream>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"
#include "sort/Sorter.h"

enum input_mode
{
	NONE,			// initial state
	IN_RANDOM,		// randomly generated file
	IN_FILE,		// input file from disk
	IN_USER			// user generated records
};

typedef struct CONFIG
{
	bool valid;
	bool step_by_step;
	bool verbosity;
	input_mode input_mode;
	std::string input_file_path;
} CONFIG;

CONFIG parse_args(int argc, char** argv)
{
	CONFIG config;
	config.valid = true;
	config.step_by_step = false;
	config.verbosity = false;
	config.input_mode = NONE;
	config.input_file_path = "";

	//if (argc == 0)
	//	config.valid = false;

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
		else if (opt == "-v" || opt == "--verbose")
		{
			config.verbosity = true;
		}
		else if (opt == "-r" || opt == "--random")
		{
			if (config.input_mode == input_mode::IN_USER ||
				config.input_mode == input_mode::IN_FILE)
			{
				std::cout << "Invalid option " << opt << " if config mode "
					<< config.input_mode << " specified before." << std::endl;
				config.valid = false;
			}
			else
			{
				config.input_mode = input_mode::IN_RANDOM;
			}
		}
		else if (opt == "-f" || opt == "--file")
		{
			if (i != opts.size() - 1)
			{
				if (config.input_mode == input_mode::IN_USER || 
					config.input_mode == input_mode::IN_RANDOM)
				{
					std::cout << "Invalid option " << opt << " if config mode "
						<< config.input_mode << " specified before." << std::endl;
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
			if (config.input_mode == input_mode::IN_FILE ||
				config.input_mode == input_mode::IN_RANDOM)
			{
				std::cout << "Invalid option " << opt << " if config mode "
					<< config.input_mode << " specified before." << std::endl;
				config.valid = false;
			}
			else
			{
				config.input_mode = IN_USER;
			}
		}
		else if (opt == "-h" || opt == "--help")
		{
			std::cout << 
				"Options:\n"
				"\n"
				"	-r, --random\n"
				"		Randomly generates input file.\n"
				"\n"
				"	-f [FILE_PATH], --file [FILE_PATH]\n"
				"		By supplying this option, the user is allowed to specify a path to the\n"
				"		binary input file.\n"
				"\n"
				"	-u, --user\n"
				"		Guides user through the process of typing the records with the keyboard.\n"
				"\n"
				"	If none of the above flags is specified, the input is generated randomly\n"
				"	just as if -r flag was provided.\n"
				"\n"
				"	-s, --step-by-step\n"
				"		Lets user go through sorting step by step. This option also sets maximum\n"
				"		verbosity.\n"
				"\n"
				"	-v, --verbose\n"
				"		Sets maximum verbosity level. This means displaying each tape during the\n"
				"		sorting process.\n";
			config.valid = false;
		}
		else
		{
			std::cout << "Unknown option " << opt << std::endl;
			config.valid = false;
		}
		i++;
	}

	if (config.input_mode == input_mode::NONE)
		config.input_mode = input_mode::IN_RANDOM;

	return config;
}

int main(int argc, char** argv)
{
	CONFIG config = parse_args(argc, argv);
	std::cout << "valid: " << config.valid << std::endl;
	std::cout << "input_mode" << config.input_mode << std::endl;
	std::cout << "step by step" << config.step_by_step << std::endl;
	std::cout << "verbosity" << config.verbosity << std::endl;

	if (!config.valid)
		return -1;

	DataGenerator data_generator;
	std::vector<Int32_Vec> data;
	std::string input_file_name;

	switch (config.input_mode)
	{
		case input_mode::IN_RANDOM:
		{
			data = data_generator.random_generate(8, 0, 10);
			input_file_name = "input/data";
			FileGenerator file_generator(input_file_name);
			file_generator.write(data);
		}
		break;
		case input_mode::IN_FILE:
			input_file_name = config.input_file_path;
		break;
		case input_mode::IN_USER:
		{
			data = data_generator.user_generate();
			input_file_name = "input/data";
			FileGenerator file_generator(input_file_name);
			file_generator.write(data);
		}
		break;
	}

	Sorter sorter("input/data4");
	//Sorter sorter("data5");
	sorter.sort(config.step_by_step, config.verbosity);

	system("pause");
	return 0;
}