#pragma once

#include <fstream>
#include <vector>

#include "DataAccessor.h"
#include "Int32_Vec.h"
#include "globals.h"

/**
 * Class handling disk write operations. Upon calling put_next() method,
 * the record is stored in a buffer. When the buffer reaches its pre-set
 * capacity, it is then written to the file. Provides block-write interface
 * for other layers of the application.
 */

class DataWriter : public DataAccessor
{
public:

	/**
	 * Series counter
	 */
	unsigned int series;

	DataWriter(std::string const & file_path, size_t buffer_size);

	~DataWriter();

	/**
	 * Appends the record r to the internal buffer. If the buffer is full,
	 * block write to the file is performed.
	 */
	void put_next(Int32_Vec r);

private:

	std::ofstream ofs;

	/**
	 * The record that was last put. Used for recognizing end of series.
	 */
	Int32_Vec last_put;

	/**
	 * Writes buffer to the file.
	 */
	void write_buffer();
};

