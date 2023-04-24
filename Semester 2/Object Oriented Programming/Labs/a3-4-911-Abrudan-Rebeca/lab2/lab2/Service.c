#define _CRT_SECURE_NO_WARNINGS
#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

Service* CreateService(Repository* repo)
{
	Service* service = (Service*)malloc(sizeof(Service));

	if (service == NULL)
		return NULL;

	service->repo = repo;

	return service;
}

void DestroyService(Service* service)
{
	free(service);
}

int UniqueCountry(Service* service, char name[], char continent[])
{
	for(size_t i = 0; i < GetLength(service->repo); ++i)
		if(strcmp(name, GetElemOnPos(service->repo, i).name) == 0 /* && (strcmp(continent, GetContinent(GetElemOnPos(
			service->repo,i))) == 0)*/) return 0;
	return 1;
}


int AddCountryService(Service* service, char name[], char continent[], double population)
{
	if (!ValidParameters(name, continent, population) || !UniqueCountry(service, name, continent)) return 1;
	Country country = createCountry(name, continent, population);
	AddCountry(service->repo, country);

	return 0;
}

int RemoveCountryService(Service* service, char name[], char continent[])
{
	int found = 1;
	for (size_t i = 0; i < GetLength(service->repo); i++)
	{
		if (strcmp(name, GetName(GetElemOnPos(service->repo, i))) == 0 &&
			 strcmp(continent, GetContinent(GetElemOnPos(service->repo, i)))==0)
		{
			found = 0;
			RemoveElement(service->repo->array, i);
		}
	}

	return found;
}
int UpdatePopulationService(Service* service, char name[], double population, double newPopulation)
{
	int found = 1;
	for (size_t i = 0; i < GetLength(service->repo); i++)
	{
		if (strcmp(name, GetName(GetElemOnPos(service->repo, i))) == 0 &&
			population == GetPopulation(GetElemOnPos(service->repo, i)))
		{
			found = 0;
			UpdatePopulation(service->repo, i, newPopulation);
		}
	}

	return found;
}

int Migration(Service* service, char country[], double peopleMigrating, char migratingToCountry[])
{
	int found = 1;
	double newPopulation, population;
	for (size_t i = 0; i < GetLength(service->repo); i++)
	{
		if (strcmp(country, GetName(GetElemOnPos(service->repo, i))) == 0) 
		{
			found = 0;
			population = GetPopulation(GetElemOnPos(service->repo, i));
			newPopulation = population - peopleMigrating;
			UpdatePopulation(service->repo, i, newPopulation);
		}
		if (strcmp(migratingToCountry, GetName(GetElemOnPos(service->repo, i))) == 0)
		{
			found = 0;
			population = GetPopulation(GetElemOnPos(service->repo, i));
			newPopulation = population + peopleMigrating;
			UpdatePopulation(service->repo, i, newPopulation);
		}
	}
	return found;
}

void GetCountryContainingString(Service* service, char searchString[], Country* result, size_t* size)
{
	*size = 0;
	char name[256];

	for (size_t i = 0; i < GetLength(service->repo); ++i)
	{
		strcpy(name, GetElemOnPos(service->repo, i).name);
		if (strstr(name, searchString))
		{
			result[*size] = GetElemOnPos(service->repo, i);
			(*size)++;
		}

	}
}

void SortByName(Country* array, size_t size)
{
	for (int i = 0; i < size - 1; ++i)
		for (int j = i + 1; j < size; ++j)
		{
			char ch1[50];
			strcpy(ch1, GetName(array[i]));
			char ch2[50];
			strcpy(ch2, GetName(array[j]));

			if (strcmp(ch1, ch2) > 0)
			{
				Country aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}
		}
}

void SortByPopulation(Country* array, size_t size)
{
	for (int i = 0; i < size - 1; ++i)
		for (int j = i + 1; j < size; ++j)
		{
			double p1 = GetPopulation(array[i]);
			double p2 = GetPopulation(array[j]);

			if (p1>p2)
			{
				Country aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}
		}
}



void GetCountryByPopulation(Service* service, Country* result, size_t* size, double value)
{
	*size = 0;
	for (size_t i = 0; i < GetLength(service->repo); ++i)
	{ 
		if (GetElemOnPos(service->repo, i).population > value)
		{
			result[*(size)] = GetElemOnPos(service->repo, i);
			(*size)++;
		}
	}
}


void GetCountryByContinentPopulation(Service* service, Country* result, size_t* size, char searchString[], double value)
{
	*size = 0;
	char name[256];
	for (size_t i = 0; i < GetLength(service->repo); ++i)
	{
		if (GetElemOnPos(service->repo, i).population > value)
		{
			strcpy(name, GetElemOnPos(service->repo, i).continent);
			if (strstr(name, searchString))
			{
				result[*(size)] = GetElemOnPos(service->repo, i);
				(*size)++;
			}
		}
	}
}

void RunAllTestsService()
{
	TestAddS();
	TestRemoveS();
	TestUpdateS();
	TestGetCountryContString();
	TestGetCountryByPopulation();
	TestGetCountryByContinentPopulation();
	TestMigration();
}

void TestAddS()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 1);
	DestroyService(service);
	DestroyRepo(repo);
}
void TestRemoveS()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAA", "A", 100);
	assert(ok == 0);
	ok = RemoveCountryService(service, "AA", "A");
	assert(ok == 0);
	ok = RemoveCountryService(service, "AA", "A");
	assert(ok == 1);

	DestroyService(service);
	DestroyRepo(repo);
}
void TestUpdateS()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAA", "A", 100);
	assert(ok == 0);
	ok = UpdatePopulationService(service, "AA", 100, 45);
	assert(ok == 0);
	ok = UpdatePopulationService(service, "AA", 101, 45);
	assert(ok == 1);

	DestroyService(service);
	DestroyRepo(repo);
}

void TestMigration()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAA", "A", 100);
	assert(ok == 0);
	ok = Migration(service, "AA", 10, "AAA");
	assert(ok == 0);

	DestroyService(service);
	DestroyRepo(repo);
}

void TestGetCountryContString()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAA", "A", 100);
	assert(ok == 0);

	Country result[60];
	size_t size;
	GetCountryContainingString(service, "A", result, &size);
	assert(strcmp(result[0].name, "AA") == 0);

	DestroyService(service);
	DestroyRepo(repo);

}

void TestGetCountryByPopulation()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAAA", "A", 100);
	assert(ok == 0);

	Country result[60];
	size_t size;
	GetCountryByPopulation(service, result, &size, 1);
	assert(strcmp(result[0].name, "AA") == 0);
	assert(strcmp(result[1].name, "AAAA") == 0);

	DestroyService(service);
	DestroyRepo(repo);
}

void TestGetCountryByContinentPopulation()
{
	Repository* repo = CreateRepo(1);
	Service* service = CreateService(repo);
	int ok = AddCountryService(service, "AA", "A", 100);
	assert(ok == 0);
	ok = AddCountryService(service, "AAAA", "A", 100);
	assert(ok == 0);

	Country result[60];
	size_t size;
	GetCountryByContinentPopulation(service, result, &size, "A", 1);
	assert(strcmp(result[0].name, "AA") == 0);
	assert(strcmp(result[1].name, "AAAA") == 0);

	GetCountryContainingString(service, "A", result, &size);
	assert(strcmp(result[0].name, "AA") == 0);

	DestroyService(service);
	DestroyRepo(repo);
}
