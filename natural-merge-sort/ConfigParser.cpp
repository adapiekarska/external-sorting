#include "ConfigParser.h"


void ConfigParser::parse_arguments(int argc, char** argv)
{
	step_by_step = false;
	verbose = false;
	buffer_size = 40;
	tapes = 2;
	records = 1000;
	min_range = 0;
	max_range = 1000;
	i_mode = NONE;
	input_file_path = "";

	std::vector<std::string> opts;
	for (int i = 1; i < argc; ++i)
		opts.push_back(argv[i]);

	unsigned int i = 0;
	while (i < opts.size())
	{
		std::string opt = opts[i];
		if (opt == "-s" || opt == "--step-by-step")
		{
			step_by_step = true;
		}
		else if (opt == "-v" || opt == "--verbose")
		{
			verbose = true;
		}
		else if (opt == "-b" || opt == "--buffer")
		{
			if (i < opts.size() - 1)
			{
				// omit the buffer size in argument parsing
				if (!opts[i + 1].empty() &&
					std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
				{
					int x = std::stoi(opts[i + 1]);
					size_t buff_size = static_cast<size_t>(x);
					if (buff_size % (sizeof(int) * VEC_DIM) == 0)
					{
						buffer_size = buff_size;
						i++;
					}
					else
						throw std::runtime_error("Buffer size must be divisible by "
							+ std::to_string(sizeof(int) * VEC_DIM));
				}
				else
					throw std::runtime_error("Missing buffer size after " + opt);
			}
			else
				throw std::runtime_error("Missing buffer size after " + opt);
		}
		else if (opt == "-t" || opt == "--tapes")
		{
			if (i < opts.size() - 1)
			{
				// omit the number of tapes in argument parsing
				if (std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
				{
					tapes = static_cast<size_t>(std::stoi(opts[i + 1]));
					i++;
				}
				else
					throw std::runtime_error("Missing tapes number after " + opt);
			}
			else
				throw std::runtime_error("Missing tapes number after " + opt);
		}
		else if (opt == "-r" || opt == "--random")
		{
			if (static_cast<int>(i) < static_cast<int>(opts.size()) - 3)
			{
				if (i_mode == input_mode::IN_USER ||
					i_mode == input_mode::IN_FILE)
				{
					std::stringstream ss;
					ss << "Invalid option " << opt << " if config mode "
						<< i_mode << " specified before.";
					throw std::runtime_error(ss.str());
				}
				else
				{
					if (std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit) &&
						std::all_of(opts[i + 2].begin(), opts[i + 2].end(), ::isdigit) &&
						std::all_of(opts[i + 3].begin(), opts[i + 3].end(), ::isdigit))
					{
						i_mode = input_mode::IN_RANDOM;
						records = static_cast<size_t>(std::stoi(opts[i + 1]));
						min_range = std::stoi(opts[i + 2]);
						max_range = std::stoi(opts[i + 3]);
						i+=3;
					}
					else
						throw std::runtime_error("Invaild arguments of " + opt[i]);
				}
			}
			else
				throw std::runtime_error("Invalid arguments of " + opt[i]);
		}
		else if (opt == "-f" || opt == "--file")
		{
			if (i < opts.size() - 1)
			{
				if (i_mode == input_mode::IN_USER ||
					i_mode == input_mode::IN_RANDOM)
				{
					std::stringstream ss;
					ss << "Invalid option " << opt << " if config mode "
						<< i_mode << " specified before.";
					throw std::runtime_error(ss.str());
				}
				else
				{
					// omit the file path in argument parsing
					if (opts[i + 1][0] != '-')
					{
						i_mode = input_mode::IN_FILE;
						input_file_path = opts[i + 1];
						std::ifstream infile(input_file_path);
						if (!infile.good())
							throw std::runtime_error("File does not exist.");
						i++;
					}
					else
						throw std::runtime_error("Missing filename after " + opt);
				}
			}
			else
				throw std::runtime_error("Missing filename after " + opt);
		}
		else if (opt == "-u" || opt == "--user")
		{
			if (i_mode == input_mode::IN_FILE ||
				i_mode == input_mode::IN_RANDOM)
			{
				std::stringstream ss;
				ss << "Invalid option " << opt << " if config mode "
					<< i_mode << " specified before.";
				throw std::runtime_error(ss.str());
			}
			else
			{
				i_mode = IN_USER;
			}
		}
		else if (opt == "-h" || opt == "--help")
		{
			std::cout <<
				"Options:\n"
				"\n"
				"	-r, --random [RECORDS_NUM] [MIN_RANGE] [MAX_RANGE]\n"
				"		Randomly generates input file containing RECORDS_NUM records from MIN_RANGE\n"
				"		to MAX_RANGE. Default is 1000.\n"
				"\n"
				"	-f, --file [FILE_PATH]\n"
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
		}
		else
			std::cout << "Unknown option " << opt << std::endl;
		i++;
	}

	if (i_mode == input_mode::NONE)
		i_mode = input_mode::IN_RANDOM;
}

bool ConfigParser::get_step_by_step()
{
	return step_by_step;
}

bool ConfigParser::get_verbose()
{
	return verbose;
}

size_t ConfigParser::get_buffer_size()
{
	return buffer_size;
}

size_t ConfigParser::get_tapes()
{
	return tapes;
}

ConfigParser::input_mode ConfigParser::get_i_mode()
{
	return i_mode;
}

size_t ConfigParser::get_records()
{
	if (i_mode != ConfigParser::input_mode::IN_RANDOM)
		throw std::runtime_error("Illegal access error.");

	return records;
}

int ConfigParser::get_min_range()
{
	if (i_mode != ConfigParser::input_mode::IN_RANDOM)
		throw std::runtime_error("Illegal access error.");

	return min_range;
}

int ConfigParser::get_max_range()
{
	if (i_mode != ConfigParser::input_mode::IN_RANDOM)
		throw std::runtime_error("Illegal access error.");

	return max_range;
}

std::string ConfigParser::get_input_file_path()
{
	if (i_mode != ConfigParser::input_mode::IN_FILE)
		throw std::runtime_error("Illegal access error.");

	return input_file_path;
}
