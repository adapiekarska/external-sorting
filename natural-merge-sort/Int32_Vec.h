#pragma once

#include <ostream>
#include <cstdint>
#include <cmath>

/**
 * Class representing the 2D vector, holding two 4 bytes integer
 * values.
 */

// TODO make this class support arbitrary number of dimensions
class Int32_Vec
{
public:

	Int32_Vec() { };
	
	Int32_Vec(int32_t first, int32_t second);
	
	~Int32_Vec();

	friend bool operator> (const Int32_Vec& v1, const Int32_Vec& v2);
	friend bool operator>= (const Int32_Vec &v1, const Int32_Vec& v2);
	friend bool operator< (const Int32_Vec& v1, const Int32_Vec& v2);
	friend bool operator<= (const Int32_Vec& v1, const Int32_Vec& v2);

	friend std::ostream &operator<<(std::ostream &output, const Int32_Vec &vec);

	int32_t first;

	int32_t second;

private:
	
	double length;
};