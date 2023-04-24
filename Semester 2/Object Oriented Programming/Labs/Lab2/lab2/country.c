#define _CRT_SECURE_NO_WARNINGS
#include "country.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

Country createCountry(char name[], char continent[], double population)
{
	Country c;
	strcpy(c.name, name);
	strcpy(c.continent, continent);
	c.population = population;
	return c;
}

char* GetName(Country c)
{
	return c.name;
}

char* GetContinent(Country c)
{
	return c.continent;
}

double GetPopulation(Country c)
{
	return c.population;
}


void SetName(Country* c, char newValue[])
{
	strcpy(c->name, newValue);
}

void SetContinent(Country* c, char newValue[])
{
	strcpy(c->continent, newValue);
}

void SetPopulation(Country* c, double newValue)
{
	c->population = newValue;
}


void Assign(Country sourceC, Country* destinationC)
{
	strcpy(destinationC->name , sourceC.name);
	strcpy(destinationC->continent , sourceC.continent);
	destinationC->population = sourceC.population;
}


char* ToString(Country country)
{
	char final_string[256] = "Name: ";
	strcat(final_string, country.name);
	strcat(final_string, " | Continent: ");

	char continent[100];
	int sizee = snprintf(continent, 100, "%s", country.continent);
	strcat(final_string, continent);
	strcat(final_string, " | Population: ");

	char population[256];
	sizee = snprintf(population, 100, "%.2f", country.population);
	strcat(final_string, population);
	strcat(final_string, "\0");

	return final_string;

}

int ValidParameters(char name[], char continent[], double population)
{
	if(!ValidName(name) || !ValidContinent(continent) || !ValidPopulation(population))
		return 0;
	return 1;
}

int ValidName(char name[])
{
	if (strlen(name) == 0) return 0;
	return 1;
}

int ValidContinent(char continent[])
{
	if (strlen(continent) == 0) return 0;
	return 1;
}

int ValidPopulation(double population)
{
	if (population > 0x3f3f3f3f) return 0;
	return 1;
}



void RunAllTestsCountry()
{
	TestGettersandSetters();
	TestAssign();
	TestValidators();
}

void TestGettersandSetters()
{
	Country c = createCountry("AA", "A", 34);
	char* name = GetName(c);
	assert(strcmp(name, "AA") == 0);
	double population;
	char* continent = GetContinent(c);
	assert(strcmp(continent, "A") == 0);
	population = GetPopulation(c);
	assert((double)population == (double)(34));

	//SetContinent(&c, 300);
	SetPopulation(&c, 123);
	//continent = GetContinent(c);
	population = GetPopulation(c);
	assert((double)population == (double)123);
}

void TestAssign()
{
	Country c = createCountry("AA", "A", 34);
	Country c2 = createCountry("AA", "A", 34);
	Assign(c, &c2);
	assert(strcmp(c.name, GetName(c2)) == 0);
	assert(strcmp(c.continent, GetContinent(c2))==0);
	assert(c.population == GetPopulation(c2));
}


void TestValidators()
{
	assert(ValidName("AA") == 1);
	assert(ValidContinent("A") == 1);
	assert(ValidPopulation(23) == 1);
	assert(ValidName("") == 0);
}
