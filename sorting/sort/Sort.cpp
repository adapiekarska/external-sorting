#include "Sort.h"


Sort::Sort()
{
}

Sort::~Sort()
{
}

void Sort::sort()
{
	std::ofstream tape1("tape1", std::ios::binary);
	std::ofstream tape2("tape2", std::ios::binary);

	DataAccessor data_accessor("out");

	while (true)
	{
		try
		{
			int32_vec v1 = data_accessor.get_next();
			int32_vec v2 = data_accessor.get_next();
		}
		catch (const EOF_Exception&)
		{
			break;
		}
	}
}
