#include "EOF_Exception.h"


const char* EOF_Exception::what() const throw()
{
	return "EOF reached.";
}