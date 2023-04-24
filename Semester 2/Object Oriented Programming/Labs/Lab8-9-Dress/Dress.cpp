#include "Dress.h"
#include <sstream>
#include<assert.h>

Dress::Dress() : size{ "" }, color{ "" }, price{ 0 }, quantity{ 0 }, photograph{ "" }
{
}

Dress::Dress(std::string size, std::string color, size_t price, size_t quantity, std::string photograph) :
	size{ size }, color{ color }, price{ price }, quantity{ quantity }, photograph{ photograph }
{
}

Dress::~Dress()
{
}

std::string Dress::GetSize() const
{
	return this->size;
}

std::string Dress::GetColor() const
{
	return this->color;
}

size_t Dress::GetPrice() const
{
	return this->price;
}

size_t Dress::GetQuantity() const
{
	return this->quantity;
}

std::string Dress::GetPhotograph() const
{
	return this->photograph;
}

void Dress::SetSize(std::string newSize)
{
	this->size = newSize;
}

void Dress::SetColor(std::string newColor)
{
	this->color = newColor;
}

void Dress::SetPrice(size_t newPrice)
{
	this->price = newPrice;
}

void Dress::SetQuantity(size_t newQuantity)
{
	this->quantity = newQuantity;
}

void Dress::SetPhotograph(std::string newPhotograph)
{
	this->photograph = newPhotograph;
}

bool Dress::operator==(const Dress& other) const
{
	return this->color == other.color;
}

std::ostream& operator<<(std::ostream& os, const Dress& dress)
{
	// // O: insert return statement here
	return os << "Size: " << dress.size << " | Color: " << dress.color << " | Price: " << dress.price << " | Quantity: "
		<< dress.quantity << " | Photograph: " << dress.photograph << "\n";

}

std::istream& operator>>(std::istream& is, Dress& dress)
{
	return is >> dress.size >>  dress.color  >> dress.price >> dress.quantity >> dress.photograph;

}

void DressTests::TestAllDresses()
{
	TestConstructorsAndGettersDress();
	TestSettersDress();
	TestEqualityDress();
	TestExtractionOperator();
}

void DressTests::TestConstructorsAndGettersDress()
{
	Dress d1;
	assert(d1.GetSize() == "");
	assert(d1.GetColor() == "");
	assert(d1.GetPrice() == 0);
	assert(d1.GetQuantity() == 0);
	assert(d1.GetPhotograph() == "");

	Dress d2("A", "B", 2, 3, "google.com");
	assert(d2.GetSize() == "A");
	assert(d2.GetColor() == "B");
	assert(d2.GetPrice() == 2);
	assert(d2.GetQuantity() == 3);
	assert(d2.GetPhotograph() == "google.com");
}

void DressTests::TestSettersDress()
{
	Dress d2;
	d2.SetSize("A");
	d2.SetColor("B");
	d2.SetPrice(2);
	d2.SetQuantity(3);
	d2.SetPhotograph("google.com");

	assert(d2.GetSize() == "A");
	assert(d2.GetColor() == "B");
	assert(d2.GetPrice() == 2);
	assert(d2.GetQuantity() == 3);
	assert(d2.GetPhotograph() == "google.com");
}

void DressTests::TestEqualityDress()
{
	Dress d1;
	d1.SetSize("A");
	d1.SetColor("B");
	d1.SetPrice(2);
	d1.SetQuantity(3);
	d1.SetPhotograph("google.com");

	Dress d2;
	d2.SetSize("A");
	d2.SetColor("B");
	d2.SetPrice(2);
	d2.SetQuantity(3);
	d2.SetPhotograph("google.com");

	assert(d1 == d2);
	d2.SetColor("X");
	assert(!(d1 == d2));
}

void DressTests::TestExtractionOperator()
{
	Dress d1;
	d1.SetSize("D");
	d1.SetColor("dd");
	d1.SetPrice(2);
	d1.SetQuantity(3);
	d1.SetPhotograph("site.ro");
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << d1;
	assert(buffer.str() == "Size: D | Color: dd | Price: 2 | Quantity: 3 | Photograph: site.ro\n");

}
