#pragma once

#include <fstream>
#include <vector>

#include "DataAccessor.h"
#include "../Record/Int32_Vec.h"
#include "../globals.h"

/**
 * Class handling disc reading operations. Read bytes are interpreted
 * as records and stored in a buffer, from where a one record is extracted in
 * case the get_next() method is called. Provides the block-read interface
 * for other layers of the application.
 */

class DataReader : public DataAccessor
{
public:

	/**
	 * Flag indicating whether the end of file has been reached. Note that
	 * this is set only after the file reader has gone past the end of file,
	 * not when the last byte is reached.
	 */
	bool eof;

	/**
	 * Flag indicating whether the end of series has been reached.
	 */
	bool eos;

	/**
	* Counter of the disc operations.
	*/
	size_t disc_ops;

	DataReader(std::string const & file_path, size_t buffer_size);

	~DataReader();

	/**
	 * Gets next record from the file.
	 */
	Int32_Vec get_next();

private:
	
	std::ifstream ifs;

	/**
	 * Most recently read record. Used in recognizing end of series.
	 */
	Int32_Vec last_read;

	/**
	 * Loads the block of records into the buffer.
	 * Returns number of the records loaded, which should be
	 * equal to buffer_size except the situation when there is
	 * less than buffer_size records left to read until EOF.
	 */
	size_t load_buffer();

};

