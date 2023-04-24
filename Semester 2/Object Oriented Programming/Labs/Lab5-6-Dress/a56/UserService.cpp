#include "UserService.h"
#include<assert.h>

UserService::UserService(Repository& repo) :
	repo{ repo }, CurrentList{ repo.GetArray() }, ShoppingBasket{ DynamicVector < Dress >(1) }, index{ 0 }, sum{0}

{
}

void UserService::AddToShoppingBasket(const Dress& dress)
{
	bool found = false;
	

	for (size_t i = 0; i < ShoppingBasket.GetSize() && !found; ++i)
		if (dress == ShoppingBasket[i]) found = true;

	if (found) throw std::exception("The dress has already been added to the shopping basket!");
	ShoppingBasket.AddElement(dress);
	sum += dress.GetPrice();
	GoToNextDress();
}


void UserService::GoToNextDress()
{
	if (index == CurrentList.GetSize() - 1)
	{
		index = 0;
		return;
	}
	index++;
}

void UserService::FilterBySize(std::string size)
{
	size_t i = 0;

	if (size != "NULL")
		while (i != CurrentList.GetSize())
		{
			if (CurrentList[i].GetSize() != size) {
				CurrentList.RemoveElement(i), i--;
			}
			i++;
		}

	index = 0;
}

void UserService::ReinitializeDressList()
{
	if (CurrentList == repo.GetArray())
		return;

	CurrentList = repo.GetArray();
	index = 0;
}

DynamicVector<Dress> UserService::GetDressList() const
{
	return ShoppingBasket;
}

Dress& UserService::GetCurrentDress() const
{
	return CurrentList[index];
}

size_t& UserService::GetSum()
{
	return sum;
}


void UserServicesTests::TestAllUser()
{
	TestConstructor();
	TestSkippingAndAddBsk();
	TestFilteringAndReinitialization();
	TestGetters();
}

void UserServicesTests::TestConstructor()
{
	Repository repo(20);
	repo.AddElement(Dress("xs", "black", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xs", "white", 150, 8, "https://google.ro"));
	repo.AddElement(Dress("s", "red", 50, 10, "https://google.ro"));
	repo.AddElement(Dress("s", "orange", 200, 7, "https://google.ro"));
	repo.AddElement(Dress("m", "yellow", 50, 5, "https://google.ro"));
	repo.AddElement(Dress("m", "green", 150, 2, "https://google.ro"));
	repo.AddElement(Dress("l", "blue", 150, 5, "https://google.ro"));
	repo.AddElement(Dress("l", "purple", 50, 3, "https://google.ro"));
	repo.AddElement(Dress("xl", "pink", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xl", "navy", 25, 1, "https://google.ro"));
	UserService s1(repo);
	assert(s1.CurrentList == repo.GetArray());
	assert(s1.index == 0);
	assert(s1.ShoppingBasket.GetSize() == 0);
}

void UserServicesTests::TestSkippingAndAddBsk()
{
	Repository repo(20);
	repo.AddElement(Dress("xs", "black", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xs", "white", 150, 8, "https://google.ro"));
	UserService s1(repo);

	s1.AddToShoppingBasket(s1.repo[s1.index]);
	assert(s1.ShoppingBasket.GetSize() == 1);
	assert(s1.GetSum() == 200);
	assert(s1.ShoppingBasket[0] == s1.repo[0]);
	assert(s1.index == 1);

	s1.GoToNextDress();
	assert(s1.index == 0);
}

void UserServicesTests::TestFilteringAndReinitialization()
{

	Repository repo(20);
	repo.AddElement(Dress("xs", "black", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xs", "white", 150, 8, "https://google.ro"));
	repo.AddElement(Dress("s", "red", 50, 10, "https://google.ro"));
	repo.AddElement(Dress("s", "orange", 200, 7, "https://google.ro"));
	repo.AddElement(Dress("m", "yellow", 50, 5, "https://google.ro"));
	repo.AddElement(Dress("m", "green", 150, 2, "https://google.ro"));
	repo.AddElement(Dress("l", "blue", 150, 5, "https://google.ro"));
	repo.AddElement(Dress("l", "purple", 50, 3, "https://google.ro"));
	repo.AddElement(Dress("xl", "pink", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xl", "navy", 25, 1, "https://google.ro"));
	UserService s1(repo);

	s1.FilterBySize("xs");
	assert(s1.CurrentList.GetSize() == 2);
	assert(s1.CurrentList[0] == Dress("xs", "black", 200, 5, "https://google.ro"));
	assert(s1.CurrentList[1] == Dress("xs", "white", 150, 8, "https://google.ro"));

	s1.ReinitializeDressList();
	assert(s1.CurrentList.GetSize() == 10);
	assert(s1.index == 0);

	s1.FilterBySize("NULL");
	assert(s1.CurrentList.GetSize() == 10);

	s1.ReinitializeDressList();
	assert(s1.CurrentList.GetSize() == 10);
	assert(s1.index == 0);
	
	s1.ReinitializeDressList();
	assert(s1.CurrentList.GetSize() == 10);
	assert(s1.index == 0);

	s1.ShoppingBasket.AddElement(Dress("xs", "black", 200, 5, "https://google.ro"));
	s1.ShoppingBasket.AddElement(Dress("xs", "white", 200, 5, "https://google.ro"));
	assert(s1.ShoppingBasket[0].GetColor() == "black");
	assert(s1.ShoppingBasket.GetSize() == 2);

	
}

void UserServicesTests::TestGetters()
{
	Repository repo(20);
	repo.AddElement(Dress("xs", "black", 200, 5, "https://google.ro"));
	repo.AddElement(Dress("xs", "white", 200, 5, "https://google.ro"));
	UserService s1(repo);

	s1.AddToShoppingBasket(s1.repo[s1.index]);

	s1.GoToNextDress();

	assert(s1.GetDressList() == s1.ShoppingBasket);
	assert(s1.GetCurrentDress() == Dress("xs", "black", 200, 5, "https://google.ro"));

	bool exceptionThrown = false;
	try {
		s1.AddToShoppingBasket(s1.repo[s1.index]);
	}
	catch (std::exception) {
		exceptionThrown = true;
	}
	assert(exceptionThrown == true);
}
