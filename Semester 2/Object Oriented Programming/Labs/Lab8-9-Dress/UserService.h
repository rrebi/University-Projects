#pragma once
#include "Repository.h"
#include "DressList.h"

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

	DressList getAll();

	std::vector<Dress> getCurrentList();

	~UserService();

	void WriteData();
	//Getters
	std::vector<Dress> GetDressList() const;

	Dress GetCurrentDress() const;
		
	size_t& GetSum();


	const std::string& GetFileName() const;
	const std::string& GetWriteMode() const;
	void SetWriteMode(const std::string& newMode);

	friend class UserServicesTests;

private:
	Repository& repo;
	std::vector<Dress> CurrentList;
	DressList dressList;
	DressListWriter* writer;
	std::vector<Dress> ShoppingBasket;
	size_t index;
	size_t sum;
	std::string writeMode;
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
