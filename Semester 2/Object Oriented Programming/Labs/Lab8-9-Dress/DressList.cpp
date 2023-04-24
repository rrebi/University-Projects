#include "DressList.h"
#include "HTMLTable.h"
#include <fstream>

DressList::DressList() :
	dressList{ std::vector<Dress>() }
{
}

void DressList::AddDress(const Dress& dog)
{
	auto pos = std::find(dressList.begin(), dressList.end(), dog);

	if (pos != dressList.end()) throw std::exception("Dress already in list!");
	dressList.push_back(dog);
}

const std::vector<Dress>& DressList::GetList() const
{
	return dressList;
}

CSVDressListWriter::CSVDressListWriter(const std::string& fileName)
{
	SetFileName(fileName);
}

void CSVDressListWriter::WriteToFile(const DressList& dressList)
{
	std::ofstream outputFile;
	outputFile.open(fileName, std::ios_base::out);

	for (auto& m : dressList.GetList())
	{
		outputFile << m.GetSize() << ',' << m.GetColor() << ',' << m.GetPrice() << ',' << m.GetQuantity() << ',' << m.GetPhotograph();
		outputFile << '\n';
	}

	outputFile.close();
}

HTMLDressListWriter::HTMLDressListWriter(const std::string& fileName)
{
	SetFileName(fileName);
}

void HTMLDressListWriter::WriteToFile(const DressList& dressList)
{
	std::ofstream outputFile;
	outputFile.open(fileName, std::ios_base::out);

	outputFile << "<!DOCTYPE html>";

	outputFile << "<html>";
	outputFile << "<head>";
	outputFile << "<title> Dress List </title>";
	outputFile << "</head>";

	outputFile << "<body>";

	HTMLTable table = HTMLTable();
	HTMLTable::Row topRow;
	topRow.AddToRow("Size");
	topRow.AddToRow("Color");
	topRow.AddToRow("Price");
	topRow.AddToRow("Quantity");
	topRow.AddToRow("Photo");
	table.AddRow(topRow);
	for (auto& m : dressList.GetList())
	{
		HTMLTable::Row newRow;
		newRow.AddToRow(m.GetSize());
		newRow.AddToRow(m.GetColor());
		newRow.AddToRow(std::to_string(m.GetPrice()));
		newRow.AddToRow(std::to_string(m.GetQuantity()));
		newRow.AddToRow(m.GetPhotograph());
		table.AddRow(newRow);
	}

	outputFile << table;

	outputFile << "</body>";

	outputFile << "</html>";

	outputFile.close();
}

const std::string& DressListWriter::GetFileName() const
{
	return fileName;
}

void DressListWriter::SetFileName(const std::string& newFile)
{
	fileName = newFile;
}
