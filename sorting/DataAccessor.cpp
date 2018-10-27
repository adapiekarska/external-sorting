#include "DataAccessor.h"



DataAccessor::DataAccessor(std::string path) : ifs(path)
{
}


DataAccessor::~DataAccessor()
{
	ifs.close();
}

Int32_Vec DataAccessor::get_next()
{
	if (buffer.empty())
		if (load() == 0)
			throw EOF_Exception();
	
	Int32_Vec next = buffer.at(0);
	buffer.erase(buffer.begin());

	return next;
}

unsigned int DataAccessor::load()
{
	// number of bytes that have to be read from the file
	std::streamsize size = BUFFER_SIZE * sizeof(int32_t) * VEC_DIM;

	std::vector<char> bytes(size);
	ifs.read(&bytes.at(0), size);

	if (ifs.eof())
		size = ifs.gcount();

	unsigned int no_ints = size / sizeof(int32_t);
	
	for (unsigned int i = 0; i < no_ints; i+=2)
	{
		int32_t first = 0, second = 0;
		// the bytes were written to file in reverse order
		for (int j = 0; j < 4; j++)
		{
			first += bytes[i * 4 + j] << (8 * j);
		}
		for (int j = 0; j < 4; j++)
		{
			second += bytes[(i+1) * 4 + j] << (8 * j);
		}
		buffer.push_back(Int32_Vec(first, second));
	}
	return no_ints * 2;
}
