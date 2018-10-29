#include "DataWriter.h"

DataWriter::DataWriter(std::string path) : ofs(path, std::ios::binary | std::istream::out)
{
	series = 1;
	disk_write_counter = 0;
}


DataWriter::~DataWriter()
{
	if (!buffer.empty())
		write_buffer();
	ofs.close();
}

void DataWriter::put_next(Int32_Vec r)
{
	if (disk_write_counter != 0 || !buffer.empty())
		if (r < last_put)
			series++;

	buffer.push_back(r);
	if (buffer.size() == BUFFER_SIZE)
		write_buffer();
	last_put = r;
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

	disk_write_counter++;
}
