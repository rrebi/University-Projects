#pragma once
#include "Repository.h"

class FileRepository :
	public Repository
{
public:
	FileRepository(const std::string& path, bool initialize = false);

	void AddElement(const Dress& newDress) override;
	void RemoveElemnt(size_t position) override;

	void UpdateSize(size_t position, std::string newS) override;
	void UpdateColor(size_t position, std::string newC) override;
	void UpdatePrice(size_t position, size_t newP) override;
	void UpdateQuantity(size_t position, size_t newQ) override;
	void UpdatePhotograph(size_t position, std::string newP) override;

	bool IsInitializable() const;
protected:
	std::string filePath;
	bool initialize;
private:
	void ReadData();
	void WriteData();
};