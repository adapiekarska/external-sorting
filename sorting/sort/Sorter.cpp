#include "Sorter.h"


Sorter::Sorter(std::string const & main_file_path, size_t tapes, size_t buffer_size) 
	: main_file_path(main_file_path), tapes(tapes), buffer_size(buffer_size), console_logger(this)
{
	disc_ops.read = 0;
	disc_ops.write = 0;
}

Sorter::~Sorter() { };


void Sorter::sort(bool step_by_step, bool verbose)
{
	size_t phases = verbose ? sort_verbose(step_by_step)
		: sort_non_verbose();
	console_logger.log_sorting_information(phases);
}

size_t Sorter::sort_verbose(bool step_by_step)
{
	console_logger.log_initial_state();
	size_t series, phases = 0;
	do
	{
		distribute();
		series = merge();

		phases++;
		console_logger.log_after_phase(phases);

		if (step_by_step)
			std::cin.get();

	} while (series > 1);

	console_logger.log_final_state();
	return phases;
}

size_t Sorter::sort_non_verbose()
{
	size_t series, phases = 0;
	do
	{
		distribute();
		series = merge();
		phases++;
	} while (series > 1);

	return phases;
}

void Sorter::distribute()
{
	DataReader input_reader(main_file_path, buffer_size);
	std::vector<DataWriter*> tape_writers;
	for (size_t i = 0; i < tapes; i++)
		tape_writers.push_back(new DataWriter("tape"+std::to_string(i), buffer_size));

	Int32_Vec prev_r, r;

	size_t current_writer_idx = 0;
	
	DataWriter* current_writer = tape_writers.at(current_writer_idx);

	// put the first record from the reader onto the first tape
	prev_r = input_reader.get_next();
	current_writer->put_next(prev_r);

	while (true)
	{
		r = input_reader.get_next();

		if (input_reader.eof)
			break;

		if (r < prev_r)
		{
			// change the tape
			current_writer_idx = (current_writer_idx + 1) % tape_writers.size();
			current_writer = tape_writers.at(current_writer_idx);
		}
		current_writer->put_next(r);
		prev_r = r;
	}

	// update disk operations counter
	for (DataWriter * writer : tape_writers)
		disc_ops.write += writer->disc_ops;

	disc_ops.read += input_reader.disc_ops;

	// delete tape writers pointers
	for (std::vector< DataWriter* >::iterator it = tape_writers.begin(); it != tape_writers.end(); ++it)
		delete (*it);
}

size_t Sorter::merge()
{
	std::vector<DataReader*> tape_readers;
	for (size_t i = 0; i < tapes; i++)
		tape_readers.push_back(new DataReader("tape" + std::to_string(i), buffer_size));

	DataWriter output_writer(main_file_path, buffer_size);

	// vector of front records from all of the tapes
	std::vector<Int32_Vec> fronts;

	// populate fronts vector
	for (std::vector<DataReader*>::iterator it = tape_readers.begin(); it != tape_readers.end();)
	{
		DataReader* reader = *it;
		Int32_Vec record = reader->get_next();
		if (reader->eof)
			it = tape_readers.erase(it);
		else
		{
			fronts.push_back(record);
			it++;
		}
	}

	std::vector<bool> stopped;
	size_t stopped_count = 0;

	for (DataReader* reader : tape_readers)
		stopped.push_back(false);

	// merging loop

	DataReader* current_reader;
	while (true)
	{
		// find the smallest record amongst all tapes' fronting records
		// ignoring the tapes that reached eos
		size_t min_tape_idx = min_tape_index(fronts, stopped);

		// put the smallest found record onto the output writer
		output_writer.put_next(fronts.at(min_tape_idx));

		// update the current reader
		current_reader = tape_readers.at(min_tape_idx);

		Int32_Vec record = current_reader->get_next();

		if (current_reader->eof)
		{
			// current reader has reached end of file
			// update disk operations counter
			disc_ops.read += tape_readers.at(min_tape_idx)->disc_ops;

			// delete the tape reader pointer
			delete tape_readers.at(min_tape_idx);

			// delete element at the index of the empty tape reader
			// from all vectors
			tape_readers.erase(tape_readers.begin() + min_tape_idx);
			fronts.erase(fronts.begin() + min_tape_idx);
			stopped.erase(stopped.begin() + min_tape_idx);

			// exit the loop if all of the readers are exhausted
			if (tape_readers.empty())
				break;
		}
		else
		{
			// update proper front element
			fronts.at(min_tape_idx) = record;
			if (current_reader->eos)
			{
				// end of series on the current reader
				stopped.at(min_tape_idx) = true;
				stopped_count++;
			}
		}

		if (stopped_count == tape_readers.size())
		{
			for (size_t i = 0; i < stopped.size(); i++)
				stopped.at(i) = false;
			stopped_count = 0;
		}
	}

	// update disk operations counter
	disc_ops.write += output_writer.disc_ops;

	// return number of series written by the output writer
	return output_writer.series;
}

size_t Sorter::min_tape_index(std::vector<Int32_Vec> const & fronts, std::vector<bool> & stopped) const
{
	size_t min;
	bool min_initialized = false;
	for (size_t i = 0; i < fronts.size(); i++)
	{
		if (!stopped.at(i)) 
		{
			if (!min_initialized)
			{
				min = i;
				min_initialized = true;
			}
			else if (fronts.at(i) < fronts.at(min))
				min = i;
		}
	}

	return min;
}
