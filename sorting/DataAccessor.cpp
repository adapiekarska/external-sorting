#include "DataAccessor.h"



DataAccessor::DataAccessor(std::string path) : ifs(path)
{
}


DataAccessor::~DataAccessor()
{
	ifs.close();
}

int32_vec DataAccessor::get_next()
{
	if (buffer.empty())
		load();
	
	int32_vec next = buffer.at(0);
	buffer.erase(buffer.begin());

	return next;
}

void DataAccessor::load()
{
	char bytes[BUFFER_SIZE * sizeof(int32_t) * VEC_DIM];

	int size = BUFFER_SIZE * sizeof(int32_t) * VEC_DIM;
	ifs.read(bytes, size);

	int no_records = size / sizeof(int32_t);
	for (int i = 0; i < no_records; i+=2)
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
		buffer.push_back(int32_vec(first, second));
	}
}
