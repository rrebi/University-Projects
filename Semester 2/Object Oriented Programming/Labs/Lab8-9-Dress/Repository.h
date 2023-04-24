#pragma once
#include "Dress.h"
#include <string>
#include <iostream>
#include <vector>

class Repository
{
public:
	/// <summary>
	/// Default constructor for dress repo
	/// </summary>
	Repository();

	/// <summary>
	/// Destructor for a dress repo
	/// </summary>
	~Repository();

	/// <summary>
	/// Adds a new dress to the repository
	/// </summary>
	/// <param name="movie">The dress to be added</param>
	virtual void AddElement(const Dress& dress);

	/// <summary>
	/// Removes a dress from the repo
	/// </summary>
	/// <param name="position">The positio of the element to be removed</param>
	virtual void RemoveElemnt(size_t position);

	/// <summary>
	/// Update the size of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be changed</param>
	/// <param name="newSize">The new size to be given to the dress</param>
	virtual void UpdateSize(size_t position, std::string newSize);

	/// <summary>
	/// Update the color of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be changed</param>
	/// <param name="newColor">The new color to be given to the dress</param>
	virtual void UpdateColor(size_t position, std::string newColor);

	/// <summary>
	/// Update the price of the dress 
	/// </summary>
	/// <param name="position">The position of the dress to be updated</param>
	/// <param name="newPrice">The new price to be given to the dress</param>
	virtual void UpdatePrice(size_t position, size_t newPrice);

	/// <summary>
	/// Update the quantity of a dress
	/// </summary>
	/// <param name="position">The postition of the dress to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the dress</param>
	virtual void UpdateQuantity(size_t position, size_t newQuantity);

	/// <summary>
	/// Update the photograph of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be updated</param>
	/// <param name="newPhotograph">The new photograph to be given to a certain dress</param>
	virtual void UpdatePhotograph(size_t position, std::string newPhotograph);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be removed</param>
	/// <returns>The position of the dress</returns>
	size_t FindElemByPhotograph(std::string photograph) const;

	size_t GetSize() const;
	std::vector<Dress> GetArray() const;

	friend class RepositoryTests;
private:
	std::vector<Dress> elementsArray;
};


class RepositoryTests
{
public:
	static void TestAllRepo();
	static void TestAdd();
	static void TestRemoveD();
	static void TestUpdate();
	static void TestFind();
	static void TestPrint();
};