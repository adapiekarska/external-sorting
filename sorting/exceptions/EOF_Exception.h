#pragma once

#include <exception>

class EOF_Exception : std::exception
{
public:
	EOF_Exception() {};
	~EOF_Exception() {};

	virtual const char* what() const throw();
};

