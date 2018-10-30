#include "FileDisplayer.h"

void FileDisplayer::display(std::string const & file_path)
{
	DataReader reader(file_path);
	Int32_Vec r;

	while (true)
	{
		r = reader.get_next();
		if (!reader.eof)
			std::cout << r << "   ";
		else
			break;
	}
	std::cout << std::endl;
}
