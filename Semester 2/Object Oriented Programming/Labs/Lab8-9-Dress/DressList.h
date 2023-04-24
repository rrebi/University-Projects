#pragma once
#include <vector>
#include "Dress.h"

class DressList
{
public:
	DressList();
	void AddDress(const Dress& dog);

	const std::vector<Dress>& GetList() const;
private:
	std::vector<Dress> dressList;
};

class DressListWriter
{
public:
	virtual void WriteToFile(const DressList& dressList) = 0;

	const std::string& GetFileName() const;
	void SetFileName(const std::string& newFile);
protected:
	std::string fileName;
};

class CSVDressListWriter : public DressListWriter
{
public:
	CSVDressListWriter(const std::string& fileName);
	void WriteToFile(const DressList& adoptionList);
};

class HTMLDressListWriter : public DressListWriter
{
public:
	HTMLDressListWriter(const std::string& fileName);
	void WriteToFile(const DressList& adoptionList);
};



