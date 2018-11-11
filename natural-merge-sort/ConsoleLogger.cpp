#include "ConsoleLogger.h"
#include "Sorter.h"


ConsoleLogger::ConsoleLogger(Sorter* sorter) : sorter(sorter), name_display_width(5)
{
	file_displayer = FileDisplayer();
}

ConsoleLogger::~ConsoleLogger() { }

void ConsoleLogger::log_after_phase(size_t i)
{
	std::cout << "====== PHASE " << i << std::endl;

	for (size_t i = 0; i < sorter->tapes; i++)
		log_tape_with_name("tape" + std::to_string(i),
			"t" + std::to_string(i));

	log_tape_with_name(sorter->main_file_path, "o");
	std::cout << std::endl;
}

void ConsoleLogger::log_initial_state()
{
	std::cout << "====== BEFORE SORT" << std::endl;
	log_tape_with_name(sorter->main_file_path, "o");
	std::cin.get();
}

void ConsoleLogger::log_final_state()
{
	std::cout << "File sorted successfully." << std::endl
		<< "Press any key to see the sorted file and sort information." << std::endl;

	std::cin.get();
	std::cout << "====== AFTER SORT" << std::endl;
	log_tape_with_name(sorter->main_file_path, "o");
	std::cout << std::endl;
}

void ConsoleLogger::log_tape_with_name(std::string const & tape_path,
	std::string const & tape_name)
{
	size_t name_len = tape_name.length();

	if (name_display_width < name_len)
		name_display_width = name_len;

	std::cout << " >";
	for (size_t i = 0; i < name_display_width - name_len - 2; i++)
		std::cout << " ";
	std::cout << tape_name << ": ";

	file_displayer.display(tape_path, sorter->buffer_size);
}

void ConsoleLogger::log_sorting_information(size_t phases, size_t th_phases, size_t th_disc_ops) const
{
	std::cout << "============ SORT INFORMATION: ============" << std::endl;
	std::cout << " number of records                : " << sorter->records << std::endl;
	std::cout << " number of tapes                  : " << sorter->tapes << std::endl;
	std::cout << " buffer size                      : " << sorter->buffer_size << std::endl;
	std::cout << " phases                           : " << phases << std::endl;
	std::cout << " theoretical phases               : " << th_phases << std::endl;
	std::cout << " disc read operations             : " << sorter->disc_ops.read << std::endl;
	std::cout << " disc write operations            : " << sorter->disc_ops.write << std::endl;
	std::cout << " total disc operations            : " << sorter->disc_ops.read + sorter->disc_ops.write << std::endl;
	std::cout << " theoretical disc operations      : " << th_disc_ops << std::endl;
	std::cout << std::endl;
}