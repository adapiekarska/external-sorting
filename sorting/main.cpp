#include <iostream>
#include <algorithm>

#include "Generators/DataGenerator.h"
#include "Generators/FileGenerator.h"
#include "Accessors/DataReader.h"
#include "Accessors/DataWriter.h"
#include "Int32_Vec.h"
#include "Sort/Sorter.h"
#include "ConfigParser.h"
//
///**
//Parses command line arguments.
//*/
//CONFIG parse_args(int argc, char** argv)
//{
//	CONFIG config;
//	config.valid = true;
//	config.step_by_step = false;
//	config.verbosity = false;
//	config.buffer_size = 40;
//	config.tapes = 2;
//	config.records = 1000;
//	config.input_mode = NONE;
//	config.input_file_path = "";
//
//	std::vector<std::string> opts;
//	for (int i = 1; i < argc; ++i)
//		opts.push_back(argv[i]);
//
//	unsigned int i = 0;
//	while (i < opts.size())
//	{
//		if (!config.valid)
//			break;
//		std::string opt = opts[i];
//		if (opt == "-s" || opt == "--step-by-step")
//		{
//			config.step_by_step = true;
//		}
//		else if (opt == "-v" || opt == "--verbose")
//		{
//			config.verbosity = true;
//		}
//		else if (opt == "-b" || opt == "--buffer")
//		{
//			if (i != opts.size() - 1)
//			{
//				// omit the buffer size in argument parsing
//				if (!opts[i + 1].empty() && 
//					std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
//				{
//					size_t buffer_size = static_cast<size_t>(std::stoi(opts[i + 1]));
//					if (buffer_size % (sizeof(int) * VEC_DIM)  == 0)
//					{
//						config.buffer_size = buffer_size;
//						i++;
//					}
//					else
//					{
//						std::cout << "Buffer size must be divisible by " 
//							<< sizeof(int) * VEC_DIM << std::endl;
//						config.valid = false;
//					}
//				}
//				else
//				{
//					std::cout << "Missing buffer size after " << opt << std::endl;
//					config.valid = false;
//				}
//			}
//			else
//			{
//				std::cout << "Missing buffer size after " << opt << std::endl;
//				config.valid = false;
//			}
//		}
//		else if (opt == "-t" || opt == "--tapes")
//		{
//			if (i != opts.size() - 1)
//			{
//				// omit the number of tapes in argument parsing
//				if (std::all_of(opts[i+1].begin(), opts[i+1].end(), ::isdigit))
//				{
//					config.tapes = static_cast<size_t>(std::stoi(opts[i + 1]));
//					i++;
//				}
//				else
//				{
//					std::cout << "Missing tapes number after " << opt << std::endl;
//					config.valid = false;
//				}
//			}
//			else
//			{
//				std::cout << "Missing tapes number after " << opt << std::endl;
//				config.valid = false;
//			}
//		}
//		else if (opt == "-r" || opt == "--random")
//		{
//			if (i != opts.size() - 1)
//			{
//				if (config.input_mode == input_mode::IN_USER ||
//					config.input_mode == input_mode::IN_FILE)
//				{
//					std::cout << "Invalid option " << opt << " if config mode "
//						<< config.input_mode << " specified before." << std::endl;
//					config.valid = false;
//				}
//				else
//				{
//					if (std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
//					{
//						config.input_mode = input_mode::IN_RANDOM;
//						config.records = static_cast<size_t>(std::stoi(opts[i + 1]));
//						i++;
//					}
//				}
//			}
//		}
//		else if (opt == "-f" || opt == "--file")
//		{
//			if (i != opts.size() - 1)
//			{
//				if (config.input_mode == input_mode::IN_USER || 
//					config.input_mode == input_mode::IN_RANDOM)
//				{
//					std::cout << "Invalid option " << opt << " if config mode "
//						<< config.input_mode << " specified before." << std::endl;
//					config.valid = false;
//				}
//				else
//				{
//					// omit the file path in argument parsing
//					if (opts[i + 1][0] != '-')
//					{
//						config.input_mode = input_mode::IN_FILE;
//						config.input_file_path = opts[i + 1];
//						i++;
//					}
//					else
//					{
//						std::cout << "Missing filename after " << opt << std::endl;
//						config.valid = false;
//					}
//				}
//			}
//			else
//			{
//				config.valid = false;
//			}
//		}
//		else if (opt == "-u" || opt == "--user")
//		{
//			if (config.input_mode == input_mode::IN_FILE ||
//				config.input_mode == input_mode::IN_RANDOM)
//			{
//				std::cout << "Invalid option " << opt << " if config mode "
//					<< config.input_mode << " specified before." << std::endl;
//				config.valid = false;
//			}
//			else
//			{
//				config.input_mode = IN_USER;
//			}
//		}
//		else if (opt == "-h" || opt == "--help")
//		{
//			std::cout <<
//				"Options:\n"
//				"\n"
//				"	-r [RECORDS_NUM], --random [RECORDS_NUM]\n"
//				"		Randomly generates input file containing RECORDS_NUM records. Default is\n"
//				"		1000.\n"
//				"\n"
//				"	-f [FILE_PATH], --file [FILE_PATH]\n"
//				"		By supplying this option, the user is allowed to specify a path to the\n"
//				"		binary input file.\n"
//				"\n"
//				"	-u, --user\n"
//				"		Guides user through the process of typing the records with the keyboard.\n"
//				"\n"
//				"	If none of the above flags is specified, the input is generated randomly\n"
//				"	just as if -r flag was provided.\n"
//				"\n"
//				"	-s, --step-by-step\n"
//				"		Lets user go through sorting step by step. This option also sets maximum\n"
//				"		verbosity.\n"
//				"\n"
//				"	-v, --verbose\n"
//				"		Sets maximum verbosity level. This means displaying each tape during the\n"
//				"		sorting process.\n"
//				"\n"
//				"	-t, --tapes [TAPES_NUM]\n"
//				"		Sets the number of tapes used in distribution phase. Default is 2.\n"
//				"\n"
//				"	-b, --buffer [BUFF_SIZE]\n"
//				"\n"
//				"		Sets the buffer size in bytes. The buffer size must be divisible by the\n"
//				"		record byte length. Default is ??B.\n"
//				"\n"
//				"	-h, --help\n"
//				"		Displays this message.\n";
//			config.valid = false;
//		}
//		else
//		{
//			std::cout << "Unknown option " << opt << std::endl;
//			config.valid = false;
//		}
//		i++;
//	}
//
//	if (config.input_mode == input_mode::NONE)
//		config.input_mode = input_mode::IN_RANDOM;
//
//	return config;
//}

int main(int argc, char** argv)
{
	ConfigParser config_parser;

	try
	{
		config_parser.parse_arguments(argc, argv);
	}
	catch (const std::runtime_error & e)
	{
		std::cout << e.what();
		return -1;
	}

	std::cout << "input_mode " << config_parser.input_mode << std::endl;
	std::cout << "step by step " << config_parser.step_by_step << std::endl;
	std::cout << "verbosity " << config_parser.verbose << std::endl;
	std::cout << "tapes " << config_parser.tapes << std::endl;
	std::cout << "record nums " << config_parser.records << std::endl;
	std::cout << "buffer size in bytes: " << config_parser.buffer_size << std::endl;

	std::cin.get();

	DataGenerator data_generator;
	std::vector<Int32_Vec> data;
	std::string input_file_name;

	switch (config_parser.input_mode)
	{
		case config_parser.input_mode::IN_RANDOM:
		{
			data = data_generator.random_generate(config_parser.records, MIN_RANGE, MAX_RANGE);
			input_file_name = "input/data";
			FileGenerator file_generator;
			file_generator.generate(data, input_file_name);
		}
		break;
		case config_parser.input_mode::IN_FILE:
		{
			input_file_name = config_parser.input_file_path;
		}
		break;
		case config_parser.input_mode::IN_USER:
		{
			data = data_generator.user_generate();
			input_file_name = "input/data";
			FileGenerator file_generator;
			file_generator.generate(data, input_file_name);
		}
		break;
	}

	Sorter sorter(input_file_name);

	sorter.sort(
		config_parser.step_by_step,
		config_parser.verbose,
		config_parser.tapes,
		config_parser.buffer_size / (sizeof(int) * VEC_DIM)
	);
	std::cin.get();
	return 0;
}