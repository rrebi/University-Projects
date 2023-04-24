#pragma once
#include <string>
#include "Dress.h"

class ValidationException
{
private:
	std::string message;

public:
	ValidationException(std::string _message);
	std::string getMessage() const;
};

class ValidationExceptionInherited : public std::exception
{
private:
	std::string message;

public:
	ValidationExceptionInherited(std::string _message);
	const char* what() const noexcept override;
};

class DressValidator
{
public:
	static void validate(const Dress& d);
};

