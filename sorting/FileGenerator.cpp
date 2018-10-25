#include "FileGenerator.h"


void FileGenerator::write(std::vector<int_vec> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		this->ofs.write(reinterpret_cast<char*>(&v.at(i).first), sizeof(int));
		this->ofs.write(reinterpret_cast<char*>(&v.at(i).second), sizeof(int));
	}
}

FileGenerator::FileGenerator(std::string path) : ofs(path, std::ios::binary)
{
}

FileGenerator::~FileGenerator()
{
	ofs.close();
}
