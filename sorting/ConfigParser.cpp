#include "ConfigParser.h"


void ConfigParser::parse_arguments(int argc, char** argv)
{
	step_by_step = false;
	verbose = false;
	buffer_size = 40;
	tapes = 2;
	records = 1000;
	input_mode = NONE;
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
			if (i != opts.size() - 1)
			{
				// omit the buffer size in argument parsing
				if (!opts[i + 1].empty() &&
					std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
				{
					size_t buffer_size = static_cast<size_t>(std::stoi(opts[i + 1]));
					if (buffer_size % (sizeof(int) * VEC_DIM) == 0)
					{
						buffer_size = buffer_size;
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
			if (i != opts.size() - 1)
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
			if (i != opts.size() - 1)
			{
				if (input_mode == input_mode::IN_USER ||
					input_mode == input_mode::IN_FILE)
				{
					std::stringstream ss;
					ss << "Invalid option " << opt << " if config mode "
						<< input_mode << " specified before.";
					throw std::runtime_error(ss.str());
				}
				else
				{
					if (std::all_of(opts[i + 1].begin(), opts[i + 1].end(), ::isdigit))
					{
						input_mode = input_mode::IN_RANDOM;
						records = static_cast<size_t>(std::stoi(opts[i + 1]));
						i++;
					}
				}
			}
		}
		else if (opt == "-f" || opt == "--file")
		{
			if (i != opts.size() - 1)
			{
				if (input_mode == input_mode::IN_USER ||
					input_mode == input_mode::IN_RANDOM)
				{
					std::stringstream ss;
					ss << "Invalid option " << opt << " if config mode "
						<< input_mode << " specified before.";
					throw std::runtime_error(ss.str());
				}
				else
				{
					// omit the file path in argument parsing
					if (opts[i + 1][0] != '-')
					{
						input_mode = input_mode::IN_FILE;
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
			if (input_mode == input_mode::IN_FILE ||
				input_mode == input_mode::IN_RANDOM)
			{
				std::stringstream ss;
				ss << "Invalid option " << opt << " if config mode "
					<< input_mode << " specified before.";
				throw std::runtime_error(ss.str());
			}
			else
			{
				input_mode = IN_USER;
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
		}
		else
			std::cout << "Unknown option " << opt << std::endl;
		i++;
	}

	if (input_mode == input_mode::NONE)
		input_mode = input_mode::IN_RANDOM;
}
