#include "FileDisplayer.h"

void FileDisplayer::display(std::string const & file_path, size_t buffer_size)
{
	DataReader reader(file_path, buffer_size);
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
