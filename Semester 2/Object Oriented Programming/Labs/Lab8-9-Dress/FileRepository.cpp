#include "FileRepository.h"
#include <fstream>


FileRepository::FileRepository(const std::string& path, bool initialize) :
	Repository{ Repository() },
	filePath{ path },
	initialize{ initialize }
{
	ReadData();
}

void FileRepository::ReadData()
{
	std::ifstream inputFile;
	inputFile.open(filePath, std::ios::in);

	Dress next;
	while (inputFile >> next)
		Repository::AddElement(next);

	inputFile.close();
}

void FileRepository::WriteData()
{
	std::ofstream outputFile;
	outputFile.open(filePath, std::ios::out);

	for (const Dress& d : Repository::GetArray())
		outputFile << d;

	outputFile.close();
}

void FileRepository::AddElement(const Dress& newD)
{
	Repository::AddElement(newD);
	WriteData();
}

void FileRepository::RemoveElemnt(size_t position)
{
	Repository::RemoveElemnt(position);
	WriteData();
}

void FileRepository::UpdateColor(size_t position, std::string newC)
{
	Repository::UpdateColor(position, newC);
	WriteData();
}

void FileRepository::UpdateSize(size_t position, std::string newS)
{
	Repository::UpdateSize(position, newS);
	WriteData();
}

void FileRepository::UpdatePrice(size_t position, size_t newp)
{
	Repository::UpdatePrice(position, newp);
	WriteData();
}

void FileRepository::UpdateQuantity(size_t position, size_t newQ)
{
	Repository::UpdateQuantity(position, newQ);
	WriteData();
}


void FileRepository::UpdatePhotograph(size_t position, std::string newP)
{
	Repository::UpdatePhotograph(position, newP);
	WriteData();
}

bool FileRepository::IsInitializable() const
{
	return initialize;
}

