#pragma once
#include "Repository.h"

class UserService
{
public:

	/// <summary>
	/// Constructor for the user servivce
	/// </summary>
	/// <param name="repo">The repository the service depends on</param>
	UserService(Repository& repo);

	/// <summary>
	/// Add an object of type dress to the basket
	/// </summary>
	/// <param name="dress">The dress we want to add to the basket</param>
	void AddToShoppingBasket(const Dress& dress);

	/// <summary>
	/// Move the index to the net dress in the list
	/// </summary>
	void GoToNextDress();

	/// <summary>
	/// Filter the shopping basket by a given size
	/// </summary>
	/// <param name="genre">The size to filter by</param>
	void FilterBySize(std::string size);

	/// <summary>
	/// Set the index to point to the beginning of the array
	/// </summary>
	void ReinitializeDressList();

	//Getters
	DynamicVector<Dress> GetDressList() const;

	Dress& GetCurrentDress() const;

	size_t& GetSum();

	friend class UserServicesTests;

private:
	Repository& repo;
	DynamicVector<Dress> CurrentList;
	DynamicVector<Dress> ShoppingBasket;
	size_t index;
	size_t sum;
};

class UserServicesTests
{
public:
	static void TestAllUser();
	static void TestConstructor();
	static void TestSkippingAndAddBsk();
	static void TestFilteringAndReinitialization();
	static void TestGetters();
};
