#include "DataWriter.h"

DataWriter::DataWriter(std::string const & file_path, size_t buffer_size)
	: DataAccessor(file_path, buffer_size), ofs(file_path, std::ios::binary | std::istream::out),
	series(1), disc_ops(0) { }

DataWriter::~DataWriter()
{
	if (!buffer.empty())
		write_buffer();
	ofs.close();
}

void DataWriter::put_next(Int32_Vec r)
{
	if (disc_ops != 0 || !buffer.empty())
		if (r < last_put)
			series++;

	if (buffer.empty())
		disc_ops++;

	buffer.push_back(r);
	if (buffer.size() == buffer_size)
		write_buffer();

	last_put = r;
}

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
