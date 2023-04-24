#include "DressValidator.h"

using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}


ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
	return message.c_str();
}


void DressValidator::validate(const Dress& s)
{
	string errors;
	if (s.GetSize().size() < 1)
		errors += string("The dress size must have at least one character!\n");

	if (s.GetColor().size() < 1)
		errors += string("The dress color must have at least one character!\n");

	if ((int)s.GetPrice() < 0)
		errors += string("The price of the dress has to be a natural number!\n");

	if ((int)s.GetQuantity() < 0)
		errors += string("The quantity of the dress has to be 0 or bigger\n");

	if (errors.size() > 0)
		throw ValidationException(errors);

	/*if (errors.size() > 0)
		throw ValidationExceptionInherited(errors);*/
}
