#include "Repository.h"
#include<sstream>
#include<assert.h>
#include<fstream>

Repository::Repository()
{
}

Repository::~Repository()
{
}

void Repository::AddElement(const Dress& dress)
{
	this->elementsArray.push_back(dress);
}

void Repository::RemoveElemnt(size_t position)
{
	this->elementsArray.erase(this->elementsArray.begin() + position);
}

void Repository::UpdateSize(size_t position, std::string newSize)
{
	this->elementsArray[position].SetSize(newSize);
}

void Repository::UpdateColor(size_t position, std::string newColor)
{
	this->elementsArray[position].SetColor(newColor);
}

void Repository::UpdatePrice(size_t position, size_t newPrice)
{
	this->elementsArray[position].SetPrice(newPrice);
}

void Repository::UpdateQuantity(size_t position, size_t newQuantity)
{
	this->elementsArray[position].SetQuantity(newQuantity);
}

void Repository::UpdatePhotograph(size_t position, std::string newPhotograph)
{
	this->elementsArray[position].SetPhotograph(newPhotograph);
}


size_t Repository::FindElemByPhotograph(std::string color) const
{
	/*size_t pos = -1;
	for (int i = 0; i < this->GetSize(); ++i)
		if ((*this->elementsArray)[i].GetColor() == color)
		{
			pos = i;
			break;
		}
	return pos;*/

	auto it = find_if(this->elementsArray.begin(), this->elementsArray.end(), [color](Dress d) {return d.GetColor() == color;}); //begin, end, predicate fct(true/false)
	if (it == this->elementsArray.end()) return -1; //not found => last

	return it - this->elementsArray.begin(); //begin => found
}

size_t Repository::GetSize() const
{
	return this->elementsArray.size();
}

std::vector<Dress> Repository::GetArray() const
{
	return this->elementsArray;
}

void RepositoryTests::TestAllRepo()
{
	TestAdd();
	TestRemoveD();
	TestUpdate();
	TestFind();
	TestPrint();
}


void RepositoryTests::TestAdd()
{
	Repository repo2{};

	Dress d1("Idk", "Idk", 1, 2, "google.com");
	Dress d2("Idk", "Idk1", 1, 2, "google.com");
	Dress d3("Idk", "Idk2", 1, 2, "google.com");
	Dress d4("Idk", "Idk3", 1, 2, "google.com");

	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	assert(repo2.GetArray()[0] == d1);
	assert(repo2.GetArray()[1] == d2);
	assert(repo2.GetArray()[2] == d3);
	assert(repo2.GetArray()[3] == d4);
}

void RepositoryTests::TestRemoveD()
{
	Repository repo2{};

	Dress d1("Idk", "Idk", 1, 2, "google.com");
	Dress d2("Idk", "Idk1", 1, 2, "google.com");
	Dress d3("Idk", "Idk2", 1, 2, "google.com");
	Dress d4("Idk", "Idk3", 1, 2, "google.com");

	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	repo2.UpdateQuantity(1, 0);

	repo2.RemoveElemnt(1);

	assert(repo2.GetArray()[0] == d1);
	assert(repo2.GetArray()[1] == d3);
	assert(repo2.GetArray()[2] == d4);}

void RepositoryTests::TestUpdate()
{
	Repository repo2{};
	Dress d1("Idk", "Idk", 1, 2, "google.com");
	repo2.AddElement(d1);

	repo2.UpdateSize(0, "A");
	repo2.UpdateColor(0, "B");
	repo2.UpdatePrice(0, 2002);
	repo2.UpdateQuantity(0, 209);
	repo2.UpdatePhotograph(0, "google.ro");
	assert(repo2.GetArray()[0].GetSize() == "A");
	assert(repo2.GetArray()[0].GetColor() == "B");
	assert(repo2.GetArray()[0].GetPrice() == 2002);
	assert(repo2.GetArray()[0].GetQuantity() == 209);
	assert(repo2.GetArray()[0].GetPhotograph() == "google.ro");
}

void RepositoryTests::TestFind()
{
	Repository repo2{};
	Dress d1("Idk", "Idk", 1, 2, "google.com");
	Dress d2("Idk", "Idk1", 1, 2, "google.com");
	Dress d3("Idkk", "Idk2", 1, 2, "google.com");
	Dress d4("Idk", "Idk3", 1, 2, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	size_t position = repo2.FindElemByPhotograph("Idk2");
	assert(position == 2);
}

void RepositoryTests::TestPrint()
{
	Repository repo{};
	Dress d1("D", "dd", 2, 3, "site.ro");
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << d1;
	assert(buffer.str() == "Size: D | Color: dd | Price: 2 | Quantity: 3 | Photograph: site.ro\n");
}



