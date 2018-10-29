#include "FileDisplayer.h"


FileDisplayer::FileDisplayer()
{
}

FileDisplayer::~FileDisplayer()
{
}

void FileDisplayer::display(std::string const & file_path)
{
	DataReader reader(file_path);
	Int32_Vec r;

	while (!reader.eof)
		std::cout << reader.get_next() << "   ";
	std::cout << std::endl;
}
