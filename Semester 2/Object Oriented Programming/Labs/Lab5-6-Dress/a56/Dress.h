#pragma once
#include <iostream>
#include <string>

class Dress
{
public:
	/// <summary>
	/// Deafult constructor for Dress class
	/// </summary>
	Dress();

	/// <summary>
	/// Constructor for the dress class + the intialization
	/// </summary>
	/// <param name="size">The size of the dress</param>
	/// <param name="color">The color of the dress</param>
	/// <param name="price">The price of the dress</param>
	/// <param name="quantity">The quantity of the dress</param>
	/// <param name="photograph">A link to the dresses photographs</param>
	Dress(std::string size, std::string color, size_t price, size_t quantity, std::string photograph);

	/// <summary>
	/// Destructor for the dress
	/// </summary>
	~Dress();

	//Getters
	std::string GetSize() const;
	std::string GetColor() const;
	size_t GetPrice() const;
	size_t GetQuantity() const;
	std::string GetPhotograph() const;

	//Setters
	void SetSize(std::string newSize);
	void SetColor(std::string newColor);
	void SetPrice(size_t newPrice);
	void SetQuantity(size_t newQuantity);
	void SetPhotograph(std::string newPhotograph);

	/// <summary>
	/// Operator "==" for the class Dress
	/// </summary>
	/// <param name="other">The dress to be compared with the other obj</param>
	/// <returns>True, if identical, False otherwise</returns>
	bool operator==(const Dress& other) const;

	/// <summary>
	/// Operator "<<" for the class Dress
	/// </summary>
	/// <param name="os"> Where the dress data is written</param>
	/// <param name="dress"> The dress whose data will be written</param>
	/// <returns> A container with the data of the dress</returns>
	friend std::ostream& operator<<(std::ostream& os, const Dress& dress);

private:
	std::string size;
	std::string color;
	size_t price;
	size_t quantity;
	std::string photograph;
};

class DressTests
{
public:
	static void TestAllDresses();
	static void TestConstructorsAndGettersDress();
	static void TestSettersDress();
	static void TestEqualityDress();
	static void TestExtractionOperator();
};