#pragma once
#include <cstdint>
#include <cmath>


class Int32_Vec
{
public:
	Int32_Vec();
	Int32_Vec(int32_t first, int32_t second);
	~Int32_Vec();

	friend bool operator> (const Int32_Vec& v1, const Int32_Vec& v2);
	friend bool operator>= (const Int32_Vec &v1, const Int32_Vec& v2);
	friend bool operator< (const Int32_Vec& v1, const Int32_Vec& v2);
	friend bool operator<= (const Int32_Vec& v1, const Int32_Vec& v2);

	int32_t first;
	int32_t second;

private:
	double length;
};

