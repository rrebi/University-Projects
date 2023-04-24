#pragma once
#include "Repository.h"
#include "Validator.h"

class AdminService
{
public:
	/// <summary>
	/// Constructor for the admin service
	/// </summary>
	/// <param name="repo">The repository on which the class service operates</param>
	AdminService(Repository& repo);

	/// <summary>
	/// Adds a new dress to the repository
	/// </summary>
	/// <param name="size">The size of the dress</param>
	/// <param name="color">The color of the dress</param>
	/// <param name="price">The price of the dress</param>
	/// <param name="quantity">The quantity of the dress</param>
	/// <param name="photograph">The photograph of the dress</param>
	void AddDress(std::string size, std::string color, size_t price, size_t quantity, std::string photgraph);

	/// <summary>
	/// Remove a certain dress from the repository
	/// </summary>
	/// <param name="photograph">The photo of the dress to be removed</param>
	void RemoveDress(std::string photograph);

	// <summary>
	/// Update the size of a dress
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be updated</param>
	/// <param name="newSize">The new size to be given to the dress</param>
	void UpdateDressSize(std::string photograph, std::string newSize);

	/// <summary>
	/// Update the color of a dress
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be changed</param>
	/// <param name="newColor">The new color to be given to the dress</param>
	void UpdateDressColor(std::string photograph, std::string newColor);

	/// <summary>
	/// Update the price of the dress 
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be updated</param>
	/// <param name="newPrice">The new price to be given to the dress</param>
	void UpdateDressPrice(std::string photograph, size_t newPrice);

	/// <summary>
	/// Update the quantity of a dress
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the dress</param>
	void UpdateDressQuantity(std::string photograph, size_t newQuantity);

	/// <summary>
	/// Update the photograph of a dress
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be updated</param>
	/// <param name="newPhotograph">The new photograph to be given to a certain dress</param>
	void UpdateDressPhotograph(std::string photograph, std::string newPhotograph);

	/// <summary>
	/// Prints the content of the repo
	/// </summary>
	/// <returns></returns>
	Repository GetRepo() const;

	/// <summary>
	/// Adds 10 entries to the repo
	/// </summary>
	void InitializeRepo();

	friend class AdminServicesTests;

private:

	Repository& repo;
};


class AdminServicesTests
{
public:
	static void TestAllAdm();
	static void TestConstructors();
	static void TestAdd();
	static void TestRemove();
	static void TestUpdate();
};


