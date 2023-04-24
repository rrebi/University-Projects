#pragma once

#include "Repository.h"

typedef struct
{
	Repository* repo;
}Service;

/// <summary>
/// Constructor for the service obj
/// </summary>
/// <param name="repo">The repo to be added to the service</param>
/// <returns>The service</returns>
Service* CreateService(Repository* repo);

/// <summary>
/// Destructor for the service object
/// </summary>
/// <param name="service">The service to be destroyed</param>
void DestroyService(Service* service);

/// <summary>
/// Add Country to the service
/// </summary>
/// <param name="service">The service to add a Country</param>
/// <param name="name">The name of the new Country to be added</param>
/// <param name="continent">The continent of the new Country to be added</param>
/// <param name="population">The population of the new Country to be added</param>
/// <returns>0 if the Country was successfully added, 1 otherwise</returns>
int AddCountryService(Service* service, char name[], char continent[], double population);

/// <summary>
/// Remove Country to the service
/// </summary>
/// <param name="service">The service to remove a Country</param>
/// <param name="name">The name of the new Country to be removed</param>
/// <param name="continent">The continent of the new Country to be removed</param>
/// <returns>0 if the Country was successfully removed, 1 otherwise</returns>
int RemoveCountryService(Service* service, char name[],  char continent[]);

/// <summary>
///  Update Country by population 
/// </summary>
/// <param name="service">The service to update a country</param>
/// <param name="name">The name of the new Country to be updated</param>
/// <param name="population">The population of the new Country to be updated</param>
/// <param name="newPopulation">The new population of the Country</param>
/// <returns>0 if the Country was successfully updated, 1 otherwise</returns>
int UpdatePopulationService(Service* service, char name[], double population, double newPopulation);

/// <summary>
/// People migrating from/to a country
/// </summary>
/// <param name="service"> The service to update a country</param>
/// <param name="country"> The country migrating from</param>
/// <param name="peopleMigrating"> no of people </param>
/// <param name="migratingToCountry"> The country they migrate to</param>
int Migration(Service* service, char country[], double peopleMigrating, char migratingToCountry[]);

/// <summary>
/// Get the Countries that contains a certain string
/// </summary>
/// <param name="service">The service to look in</param>
/// <param name="searchString">the string to be searched</param>
/// <param name="result">the Countries that contains the given string</param>
/// <param name="size">the size ofthe result</param>
void GetCountryContainingString(Service* service, char searchString[], Country* result, size_t* size);

/// <summary>
/// Sort the Country by name
/// </summary>
/// <param name="array">The array to be sorted</param>
/// <param name="size">The size of the array</param>
void SortByName(Country* array, size_t size);

/// <summary>
/// Sort the Country by population
/// </summary>
/// <param name="array">The array to be sorted</param>
/// <param name="size">The size of the array</param>
void SortByPopulation(Country* array, size_t size);

/// <summary>
/// Get the Countries with population less than a given population
/// </summary>
/// <param name="service">The service to look in</param>
/// <param name="result">The Countries that respects the given criteria</param>
/// <param name="size">The length of the result</param>
/// <param name="value">The value to search by</param>
void GetCountryByPopulation(Service* service, Country* result, size_t* size, double value);

/// <summary>
/// Get the Countries from continent with population less than a given population
/// </summary>
/// <param name="service">The service to look in</param>
/// <param name="result">The Countries that respects the given criteria</param>
/// <param name="size">The length of the result</param>
/// <param name="searchString">the string to be searched</param>
/// <param name="value">The value to search by</param>
void GetCountryByContinentPopulation(Service* service, Country* result, size_t* size, char searchString[], double value);

void RunAllTestsService();
void TestAddS();
void TestRemoveS();
void TestUpdateS();
void TestMigration();
void TestGetCountryContString();
void TestGetCountryByPopulation();
void TestGetCountryByContinentPopulation();