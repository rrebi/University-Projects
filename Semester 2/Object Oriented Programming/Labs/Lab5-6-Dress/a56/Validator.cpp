#include "Validator.h"
#include <regex>

bool Validator::ValidDressAttributes(std::string size, std::string color, size_t price, size_t quantity, std::string photograph)
{
    return ValidDressSize(size) && ValidDressColor(color) && ValidDressPrice(price) && ValidDressQuantity(quantity) && ValidDressPhotograph(photograph);
}

bool Validator::ValidDressSize(std::string size)
{
    return !size.empty();
}

bool Validator::ValidDressColor(std::string color)
{
    return !color.empty();
}

bool Validator::ValidDressPrice(size_t price)
{
    return price > 0;
}

bool Validator::ValidDressQuantity(size_t quantity)
{
    return quantity >= 0;
}

bool Validator::ValidDressPhotograph(std::string photograph)
{
    //return std::regex_match(photograph, std::regex("(^https:\/\/)?([a-zA-Z])+\.([a-z]{2,})(\/(.)+)?"));
    return !photograph.empty();
}
