#pragma once
#include "Dress.h"

class Validator
{
public:
	static bool ValidDressAttributes(std::string size, std::string color, size_t price, size_t quantity, std::string photograph);
	static bool ValidDressSize(std::string size);
	static bool ValidDressColor(std::string color);
	static bool ValidDressPrice(size_t price);
	static bool ValidDressQuantity(size_t quantity);
	static bool ValidDressPhotograph(std::string photograph);
private:

};
