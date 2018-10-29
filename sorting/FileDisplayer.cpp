#include "FileDisplayer.h"

void FileDisplayer::display(std::string const & file_path)
{
	DataReader reader(file_path);
	Int32_Vec r;

	while (true)
	{
		std::cout << reader.get_next() << "   ";
		if (reader.eof)
			break;
	}
	std::cout << std::endl;
}
