#pragma once

#include <vector>
#include <string>

#include "Int32_Vec.h"

/**
 * Base class for DataWriter and DataReader.
 */

class DataAccessor
{
public:

	DataAccessor(std::string const & file_path, size_t buffer_size);
	
	virtual ~DataAccessor() { };

protected:

	/**
	 * Path to file that the accessor handles
	 */
	std::string file_path;
	
	/**
	 * Buffer size in number of records
	 */
	size_t buffer_size;

	/**
	 * Buffer of records
	 */
	std::vector<Int32_Vec> buffer;

};

