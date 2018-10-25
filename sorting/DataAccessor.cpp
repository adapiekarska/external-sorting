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
	
	int_vec next = buffer.at(0);
	buffer.erase(buffer.begin());
	return next;
}

void DataAccessor::load()
{
	int32_t first, second;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		ifs.read(reinterpret_cast<char*>(&first), sizeof(int32_t));
		ifs.read(reinterpret_cast<char*>(&second), sizeof(int32_t));
		buffer.push_back(int_vec(first, second));
	}
}
