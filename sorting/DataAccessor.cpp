#include "DataAccessor.h"



DataAccessor::DataAccessor(std::string path) : ifs(path)
{
}


DataAccessor::~DataAccessor()
{
	ifs.close();
}

int_vec DataAccessor::get_next()
{
	if (buffer.empty())
		load();
}

void DataAccessor::load()
{
	uint32_t first, second;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		ifs.read(reinterpret_cast<char *>(&first), sizeof(uint32_t));
		ifs.read(reinterpret_cast<char *>(&second), sizeof(uint32_t));
		buffer.push_back(int_vec(first, second));
	}
}
