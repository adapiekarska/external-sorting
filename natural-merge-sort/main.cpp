#include <iostream>
#include <algorithm>

#include "DataGenerator.h"
#include "FileGenerator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "Int32_Vec.h"
#include "Sorter.h"
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

	DataGenerator data_generator;
	std::vector<Int32_Vec> data;
	std::string input_file_name = "data";

	switch (config_parser.get_i_mode())
	{
		case config_parser.input_mode::IN_RANDOM:
		{
			data = data_generator.random_generate(config_parser.get_records(), config_parser.get_min_range(), config_parser.get_max_range());
			FileGenerator file_generator;
			file_generator.generate(data, input_file_name);
		}
		break;
		case config_parser.input_mode::IN_FILE:
		{
			input_file_name = config_parser.get_input_file_path();
		}
		break;
		case config_parser.input_mode::IN_USER:
		{
			data = data_generator.user_generate();
			FileGenerator file_generator;
			file_generator.generate(data, input_file_name);
		}
		break;
	}

	Sorter sorter(input_file_name, config_parser.get_tapes(), config_parser.get_buffer_size() / (sizeof(int) * VEC_DIM));
	std::cout << "Starting sort..." << std::endl;
	std::cout << std::endl;
	sorter.sort(
		config_parser.get_step_by_step(),
		config_parser.get_verbose()
	);
	std::cout << "Program finished." << std::endl;
	return 0;
}