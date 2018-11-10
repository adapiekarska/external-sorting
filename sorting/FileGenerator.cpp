#include "FileGenerator.h"

void FileGenerator::generate(std::vector<Int32_Vec> &v, std::string const &path)
{
	std::ofstream ofs(path, std::ios::binary);

	for (unsigned int i = 0; i < v.size(); i++)
	{
		ofs.write(reinterpret_cast<char*>(&v.at(i).first), sizeof(int32_t));
		ofs.write(reinterpret_cast<char*>(&v.at(i).second), sizeof(int32_t));
	}
	ofs.close();
}
