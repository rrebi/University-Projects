#include "Repository.h"
#include<sstream>
#include<assert.h>
#include<fstream>

Repository::Repository() :
	elementsArray{ nullptr }
{
}

Repository::Repository(size_t maxSize) :
	elementsArray{ new DynamicVector<Dress>(maxSize) }
{
}

Repository::Repository(const Repository& other) :
	elementsArray{ new DynamicVector<Dress>(*other.elementsArray) }
{
}

Repository::~Repository()
{
	delete this->elementsArray;
	this->elementsArray = nullptr;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string>result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, ','))
		result.push_back(token);

	return result;
}

Repository& Repository::operator=(const Repository& other)
{
	// // O: insert return statement here
	if (this == &other) return *this;

	if (this->elementsArray == nullptr) this->elementsArray = new DynamicVector<Dress>();
	*this->elementsArray = *other.elementsArray;

	return *this;
}

Dress& Repository::operator[](size_t position)
{
	// // O: insert return statement here
	return (*this->elementsArray)[position];
}

bool Repository::operator==(const Repository& other) const
{
	return *this->elementsArray == *other.elementsArray;
}

void Repository::AddElement(const Dress& dress)
{
	*this->elementsArray + dress;
}

void Repository::RemoveElemnt(size_t position)
{
	this->elementsArray->RemoveElement(position);
}

void Repository::UpdateSize(size_t position, std::string newSize)
{
	(*this->elementsArray)[position].SetSize(newSize);
}

void Repository::UpdateColor(size_t position, std::string newColor)
{
	(*this->elementsArray)[position].SetColor(newColor);
}

void Repository::UpdatePrice(size_t position, size_t newPrice)
{
	(*this->elementsArray)[position].SetPrice(newPrice);
}

void Repository::UpdateQuantity(size_t position, size_t newQuantity)
{
	(*this->elementsArray)[position].SetQuantity(newQuantity);
}

void Repository::UpdatePhotograph(size_t position, std::string newPhotograph)
{
	(*this->elementsArray)[position].SetPhotograph(newPhotograph);
}

std::ostream& operator<<(std::ostream& os, const Repository& repo)
{
	os << *repo.elementsArray; return os;
}

size_t Repository::FindElemByPhotograph(std::string color) const
{
	size_t pos = -1;
	for (int i = 0; i < this->GetSize(); ++i)
		if ((*this->elementsArray)[i].GetColor() == color)
		{
			pos = i;
			break;
		}
	return pos;
}

size_t Repository::GetSize() const
{
	return this->elementsArray->GetSize();
}

DynamicVector<Dress> Repository::GetArray() const
{
	return *this->elementsArray;
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

	assert(repo2[0] == d1);
	assert(repo2[1] == d2);
	assert(repo2[2] == d3);
	assert(repo2[3] == d4);
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

	assert(repo2[0] == d1);
	assert(repo2[1] == d3);
	assert(repo2[2] == d4);
}

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
	assert(repo2[0].GetSize() == "A");
	assert(repo2[0].GetColor() == "B");
	assert(repo2[0].GetPrice() == 2002);
	assert(repo2[0].GetQuantity() == 209);
	assert(repo2[0].GetPhotograph() == "google.ro");
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

	os << repo;
}



