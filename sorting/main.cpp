#include <iostream>
#include <algorithm>

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
	size_t buffer_size;
	size_t tapes;
	size_t records;
	input_mode input_mode;
	std::string input_file_path;
} CONFIG;

CONFIG parse_args(int argc, char** argv)
{
	CONFIG config;
	config.valid = true;
	config.step_by_step = false;
	config.verbosity = false;
	config.buffer_size = 40;
	config.tapes = 2;
	config.records = 1000;
	config.input_mode = NONE;
	config.input_file_path = "";

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
		else if (opt == "-b" || opt == "--buffer")
		{
			if (i != opts.size() - 1)
			{
				// omit the buffer size in argument parsing
				if (!opts[i + 1].empty() && std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
				{
					size_t buffer_size = static_cast<size_t>(std::stoi(opts[i + 1]));
					if (buffer_size % (sizeof(int) * VEC_DIM)  == 0)
					{
						config.buffer_size = buffer_size;
						i++;
					}
					else
					{
						std::cout << "Buffer size must be divisible by " << sizeof(int) * VEC_DIM << std::endl;
						config.valid = false;
					}
				}
				else
				{
					std::cout << "Missing buffer size after " << opt << std::endl;
					config.valid = false;
				}
			}
			else
			{
				std::cout << "Missing buffer size after " << opt << std::endl;
				config.valid = false;
			}
		}
		else if (opt == "-t" || opt == "--tapes")
		{
			if (i != opts.size() - 1)
			{
				// omit the number of tapes in argument parsing
				if (std::all_of(opts[i+1].begin(), opts[i+1].end(), ::isdigit))
				{
					config.tapes = static_cast<size_t>(std::stoi(opts[i + 1]));
					i++;
				}
				else
				{
					std::cout << "Missing tapes number after " << opt << std::endl;
					config.valid = false;
				}
			}
			else
			{
				std::cout << "Missing tapes number after " << opt << std::endl;
				config.valid = false;
			}
		}
		else if (opt == "-r" || opt == "--random")
		{
			if (i != opts.size() - 1)
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
					if (std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
					{
						config.input_mode = input_mode::IN_RANDOM;
						config.records = static_cast<size_t>(std::stoi(opts[i + 1]));
						i++;
					}
				}
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
					if (opts[i + 1][0] != '-')
					{
						config.input_mode = input_mode::IN_FILE;
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
				"	-r [RECORDS_NUM], --random [RECORDS_NUM]\n"
				"		Randomly generates input file containing RECORDS_NUM records. Default is\n"
				"		1000.\n"
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
				"		sorting process.\n"
				"\n"
				"	-t, --tapes [TAPES_NUM]\n"
				"		Sets the number of tapes used in distribution phase. Default is 2.\n"
				"\n"
				"	-b, --buffer [BUFF_SIZE]\n"
				"\n"
				"		Sets the buffer size in bytes. The buffer size must be divisible by the\n"
				"		record byte length. Default is ??B.\n"
				"\n"
				"	-h, --help\n"
				"		Displays this message.\n";
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
	std::cout << "input_mode " << config.input_mode << std::endl;
	std::cout << "step by step " << config.step_by_step << std::endl;
	std::cout << "verbosity " << config.verbosity << std::endl;
	std::cout << "tapes " << config.tapes << std::endl;
	std::cout << "record nums " << config.records << std::endl;
	std::cout << "buffer size in bytes: " << config.buffer_size << std::endl;

	system("pause");

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

	Sorter sorter("input/data3");
	sorter.sort(config.step_by_step, config.verbosity, config.tapes, config.buffer_size);

	system("pause");
	return 0;
}