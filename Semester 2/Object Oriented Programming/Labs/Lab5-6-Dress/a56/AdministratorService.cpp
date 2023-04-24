#include "AdministratorService.h"
#include <exception>
#include<assert.h>

AdminService::AdminService(Repository& repo) :
	repo{ repo }
{
}

void AdminService::AddDress(std::string size, std::string color, size_t price, size_t quantity, std::string photgraph)
{
	if (!Validator::ValidDressAttributes(size, color, price, quantity, photgraph))
		throw std::exception("Invalid dress parameters!!");

	Dress newDress = Dress(size, color, price, quantity, photgraph);

	bool duplicate = false;
	for (size_t i = 0; i < this->repo.GetSize(); ++i)
		if (this->repo[i] == newDress) duplicate = true;

	if (duplicate) throw std::exception("A dress with the same color already exists!");

	this->repo.AddElement(newDress);
}

void AdminService::RemoveDress(std::string photograph)
{
	size_t pos = this->repo.FindElemByPhotograph(photograph);
	if (pos >= this->repo.GetSize())
		throw std::exception("Dress not found!");
	if (this->repo[pos].GetQuantity() != 0)
		throw std::exception("Quantity not 0!");
	this->repo.RemoveElemnt(pos);
}

void AdminService::UpdateDressSize(std::string photograph, std::string newSize)
{
	if (!Validator::ValidDressSize) throw std::exception("Invalid dress!");
	size_t pos = this->repo.FindElemByPhotograph(photograph);

	if (pos > this->repo.GetSize()) throw std::exception("Dress not found!");
	this->repo.UpdateSize(pos, newSize);
}

void AdminService::UpdateDressColor(std::string photograph, std::string newColor)
{
	if (!Validator::ValidDressColor) throw std::exception("Invalid dress!");
	size_t pos = this->repo.FindElemByPhotograph(photograph);

	
	bool duplicate = false;
	for (size_t i = 0; i < this->repo.GetSize(); ++i)
		if (this->repo[i].GetColor() == newColor) duplicate = true;

	if (duplicate) throw std::exception("A dress with the same color already exists!");

	if (pos > this->repo.GetSize()) throw std::exception("Dress not found!");
	this->repo.UpdateColor(pos, newColor);
}

void AdminService::UpdateDressPrice(std::string photograph, size_t newPrice)
{
	if (!Validator::ValidDressPrice) throw std::exception("Invalid dress!");
	size_t pos = this->repo.FindElemByPhotograph(photograph);

	if (pos > this->repo.GetSize()) throw std::exception("Dress not found!");
	this->repo.UpdatePrice(pos, newPrice);
}

void AdminService::UpdateDressQuantity(std::string photograph, size_t newQuantity)
{
	if (!Validator::ValidDressQuantity) throw std::exception("Invalid dress!");
	size_t pos = this->repo.FindElemByPhotograph(photograph);

	if (pos > this->repo.GetSize()) throw std::exception("Dress not found!");
	this->repo.UpdateQuantity(pos, newQuantity);
}

void AdminService::UpdateDressPhotograph(std::string photograph, std::string newPhotograph)
{
	if (!Validator::ValidDressPhotograph) throw std::exception("Invalid dress!");
	size_t pos = this->repo.FindElemByPhotograph(photograph);

	if (pos > this->repo.GetSize()) throw std::exception("Dress not found!");
	this->repo.UpdatePhotograph(pos, newPhotograph);
}

Repository AdminService::GetRepo() const
{
	return this->repo;
}

void AdminService::InitializeRepo()
{
	AddDress("xs", "black", 200, 5, "https://google.ro");
	AddDress("xs", "white", 150, 8, "https://google.ro");
	AddDress("s", "red", 50, 10, "https://google.ro");
	AddDress("s", "orange", 200, 7, "https://google.ro");
	AddDress("m", "yellow", 50, 5, "https://google.ro");
	AddDress("m", "green", 150, 2, "https://google.ro");
	AddDress("l", "blue", 150, 5, "https://google.ro");
	AddDress("l", "purple", 50, 3, "https://google.ro");
	AddDress("xl", "pink", 200, 5, "https://google.ro");
	AddDress("xl", "navy", 25, 1, "https://google.ro");
}

void AdminServicesTests::TestAllAdm()
{
	TestConstructors();
	TestAdd();
	TestRemove();
	TestUpdate();
}

void AdminServicesTests::TestConstructors()
{
	Repository repo(20);
	AdminService s2(repo);
	assert(s2.repo.GetSize() == 0);
	assert(s2.GetRepo() == repo);
}

void AdminServicesTests::TestAdd()
{
	Repository repo(20);
	AdminService s2(repo);
	s2.AddDress("xs", "black", 33, 33, "https://google.ro");
	assert(s2.repo[0].GetSize() == "xs");
	assert(s2.repo[0].GetColor() == "black");
	assert(s2.repo[0].GetPrice() == 33);
	assert(s2.repo[0].GetQuantity() == 33);
	assert(s2.repo[0].GetPhotograph() == "https://google.ro");

	s2.AddDress("xs", "white", 33, 33, "https://google.ro");
	assert(s2.repo[1].GetSize() == "xs");
	assert(s2.repo[1].GetColor() == "white");
	assert(s2.repo[1].GetPrice() == 33);
	assert(s2.repo[1].GetQuantity() == 33);
	assert(s2.repo[1].GetPhotograph() == "https://google.ro");

	bool exceptionThrown = false;
	try {
		s2.AddDress("xs", "x", 0, 0, "https://google.ro");
	}
	catch (std::exception) {
		exceptionThrown = true;
	}
	assert(exceptionThrown == true);
}

void AdminServicesTests::TestRemove()
{
	Repository repo(20);
	AdminService s2(repo);
	s2.InitializeRepo();
	assert(s2.repo[0].GetSize() == "xs");
	assert(s2.repo[0].GetColor() == "black");
	assert(s2.repo[0].GetPrice() == 200);
	assert(s2.repo[0].GetQuantity() == 5);
	assert(s2.repo[0].GetPhotograph() == "https://google.ro");

	bool exceptionThrown = false;
	try {
		s2.RemoveDress("black");
	}
	catch (std::exception) {
		exceptionThrown = true;
	}
	assert(exceptionThrown == true);
	
	bool exceptionThrown1 = false;
	try {
		s2.RemoveDress("f");
	}
	catch (std::exception) {
		exceptionThrown1 = true;
	}
	assert(exceptionThrown1 == true);

	s2.UpdateDressQuantity("black", 0);

	s2.RemoveDress("black");
	assert(s2.repo[0].GetSize() == "xs");
	assert(s2.repo[0].GetColor() == "white");
	assert(s2.repo[0].GetPrice() == 150);
	assert(s2.repo[0].GetQuantity() == 8);
	assert(s2.repo[0].GetPhotograph() == "https://google.ro");

}

void AdminServicesTests::TestUpdate()
{
	Repository repo(20);
	AdminService s2(repo);
	s2.InitializeRepo();

	assert(s2.repo[0].GetSize() == "xs");
	assert(s2.repo[0].GetColor() == "black");
	assert(s2.repo[0].GetPrice() == 200);
	assert(s2.repo[0].GetQuantity() == 5);
	assert(s2.repo[0].GetPhotograph() == "https://google.ro");


	s2.UpdateDressColor("black", "rr");
	assert(s2.repo[0].GetColor() == "rr");

	s2.UpdateDressSize("rr", "s");
	s2.UpdateDressPrice("rr", 3333);
	s2.UpdateDressQuantity("rr", 333);
	s2.UpdateDressPhotograph("rr", "https://dress.ro");

	assert(s2.repo[0].GetSize() == "s");
	assert(s2.repo[0].GetPrice() == 3333);
	assert(s2.repo[0].GetQuantity() == 333);
	assert(s2.repo[0].GetPhotograph() == "https://dress.ro");


}
