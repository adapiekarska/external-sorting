#include "DataWriter.h"
#include <iostream>	// TODO Remove

DataWriter::DataWriter(std::string path) : ofs(path, std::ios::binary | std::istream::out)
{
}


DataWriter::~DataWriter()
{
	if (!buffer.empty())
		write_buffer();
	ofs.close();
}

void DataWriter::put_next(Int32_Vec r)
{
	buffer.push_back(r);
	if (buffer.size() == BUFFER_SIZE)
		write_buffer();
}

// TODO change for loops

void DataWriter::write_buffer()
{
	std::vector<char> bytes;
	int32_t mask = 255;
	while (!buffer.empty())
	{
		Int32_Vec v = buffer.front();
		buffer.erase(buffer.begin());

		for (int i = 0; i < 4; i++)
		{
			bytes.push_back(v.first & mask);
			v.first >>= 8;
		}
		for (int i = 0; i < 4; i++)
		{
			bytes.push_back(v.second & mask);
			v.second >>= 8;

		}
	}

	ofs.write(bytes.data(), bytes.size());
}
