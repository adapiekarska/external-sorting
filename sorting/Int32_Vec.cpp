#include "Int32_Vec.h"


Int32_Vec::Int32_Vec(int32_t first, int32_t second) : first(first), second(second)
{
	length = sqrt(first * first + second * second);
}

Int32_Vec::~Int32_Vec() { }

bool operator>(const Int32_Vec & v1, const Int32_Vec & v2)
{
	//return v1.length > v2.length;
	return v1.first > v2.first;
}

bool operator>=(const Int32_Vec & v1, const Int32_Vec & v2)
{
	// return v1.length >= v2.length;
	return v1.first >= v2.first;
}

bool operator<(const Int32_Vec & v1, const Int32_Vec & v2)
{
	//return v1.length < v2.length;
	return v1.first < v2.first;
}

bool operator<=(const Int32_Vec & v1, const Int32_Vec & v2)
{
	// return v1.length <= v2.length;
	return v1.first <= v2.first;
}

std::ostream & operator<<(std::ostream & output, const Int32_Vec & vec)
{
	output << vec.first << " " << vec.second;
	return output;
}
