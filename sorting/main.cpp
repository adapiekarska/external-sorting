#include <iostream>
#include <algorithm>

#include "DataUtilities/DataGenerator.h"
#include "FileUtilities/FileGenerator.h"
#include "Accessors/DataReader.h"
#include "Accessors/DataWriter.h"
#include "Record/Int32_Vec.h"
#include "Sort/Sorter.h"
#include "ConfigParser.h"


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

	/*std::cout << "input_mode " << config_parser.input_mode << std::endl;
	std::cout << "step by step " << config_parser.step_by_step << std::endl;
	std::cout << "verbosity " << config_parser.verbose << std::endl;
	std::cout << "tapes " << config_parser.tapes << std::endl;
	std::cout << "record nums " << config_parser.records << std::endl;
	std::cout << "buffer size in bytes: " << config_parser.buffer_size << std::endl;

	std::cin.get();
*/
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

	Sorter sorter(input_file_name, config_parser.tapes, config_parser.buffer_size / (sizeof(int) * VEC_DIM));
	sorter.sort(
		config_parser.step_by_step,
		config_parser.verbose
	);
	std::cin.get();
	return 0;
}