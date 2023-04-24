#pragma once
#include "Dress.h"
#include "DynamicVector.h"
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
	/// Constructor which initialize the repo with a dynamic array of a given size
	/// </summary>
	/// <param name="maxSize">The capacity of the dynamic array</param>
	Repository(size_t maxSize);

	/// <summary>
	/// Copy constructor for a dress repo
	/// </summary>
	/// <param name="other">The repo to copy to</param>
	Repository(const Repository& other);

	/// <summary>
	/// Destructor for a dress repo
	/// </summary>
	~Repository();

	/// <summary>
	/// Copy a repo to another
	/// </summary>
	/// <param name="other">The repo to be copied</param>
	/// <returns>An object with the same elements as the existing one</returns>
	Repository& operator=(const Repository& other);

	/// <summary>
	/// Indexing operator for dress repository
	/// </summary>
	/// <param name="position">The position of the element to be returned</param>
	/// <returns>The element</returns>
	Dress& operator[](size_t position);

	/// <summary>
	/// Equality of two elements
	/// </summary>
	/// <param name="other">The object to compare to</param>
	/// <returns>true if they are the same, false otherwise</returns>
	bool operator==(const Repository& other) const;

	/// <summary>
	/// Insertion operator for the repository class
	/// </summary>
	/// <param name="os">The stream object to write to</param>
	/// <param name="repo">The repo to be written</param>
	/// <returns>A stream containing the elements of the repository</returns>
	friend std::ostream& operator<<(std::ostream& os, const Repository& repo);

	/// <summary>
	/// Adds a new dress to the repository
	/// </summary>
	/// <param name="movie">The dress to be added</param>
	void AddElement(const Dress& dress);

	/// <summary>
	/// Removes a dress from the repo
	/// </summary>
	/// <param name="position">The positio of the element to be removed</param>
	void RemoveElemnt(size_t position);

	/// <summary>
	/// Update the size of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be changed</param>
	/// <param name="newSize">The new size to be given to the dress</param>
	void UpdateSize(size_t position, std::string newSize);

	/// <summary>
	/// Update the color of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be changed</param>
	/// <param name="newColor">The new color to be given to the dress</param>
	void UpdateColor(size_t position, std::string newColor);

	/// <summary>
	/// Update the price of the dress 
	/// </summary>
	/// <param name="position">The position of the dress to be updated</param>
	/// <param name="newPrice">The new price to be given to the dress</param>
	void UpdatePrice(size_t position, size_t newPrice);

	/// <summary>
	/// Update the quantity of a dress
	/// </summary>
	/// <param name="position">The postition of the dress to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the dress</param>
	void UpdateQuantity(size_t position, size_t newQuantity);

	/// <summary>
	/// Update the photograph of a dress
	/// </summary>
	/// <param name="position">The position of the dress to be updated</param>
	/// <param name="newPhotograph">The new photograph to be given to a certain dress</param>
	void UpdatePhotograph(size_t position, std::string newPhotograph);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="photograph">The photograph of the dress to be removed</param>
	/// <returns>The position of the dress</returns>
	size_t FindElemByPhotograph(std::string photograph) const;

	size_t GetSize() const;
	DynamicVector<Dress> GetArray() const;
	
	friend class RepositoryTests;
private:
	DynamicVector<Dress>* elementsArray;
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