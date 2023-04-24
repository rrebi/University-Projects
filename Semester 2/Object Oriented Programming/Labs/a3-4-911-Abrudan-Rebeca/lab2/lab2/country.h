#pragma once
#include <stddef.h>

typedef struct
{
	char name[50];
	char continent[50];
	double population;
} Country;

/// <summary>
/// Constructor for a Country object
/// </summary>
/// <param name="name">the name of the Country</param>
/// <param name="continent">the continent of the Country</param>
/// <param name="population">the populaton of the Country</param>
/// <returns>the created obj</returns>
Country createCountry(char name[], char continent[], double population);

/// <summary>
/// Getter for the name of a Country
/// </summary>
/// <param name="country">the Country obj</param>
/// <returns>the name of the Country</returns>
char* GetName(Country country);

/// <summary>
/// Getter for the continent of a Country
/// </summary>
/// <param name="country">The Country obj</param>
/// <returns>the continent of the Country</returns>
char* GetContinent(Country country);

/// <summary>
/// Getter for the population of a medicine
/// </summary>
/// <param name="country">The Country obj</param>
/// <returns>the population of the Country</returns>
double GetPopulation(Country country);


/// <summary>
/// Setter for the name of a Country 
/// </summary>
/// <param name="Country">The Country object</param>
/// <param name="newValue">The new name to be set</param>
void SetName(Country* country, char newValue[]);

/// <summary>
/// Setter for the continent of a Country
/// </summary>
/// <param name="Country">The Country obj</param>
/// <param name="newValue">The new continent to be set</param>
void SetContinent(Country* country, char newValue[]);

/// <summary>
/// Setter for the population of a Country
/// </summary>
/// <param name="Country">The Country obj</param>
/// <param name="newValue">The new population to be set</param>
void SetPopulation(Country* country, double newValue);

/// <summary>
///  Make a copy of a Country
/// </summary>
/// <param name="sourceC">the Country to be copied</param>
/// <param name="destinationC">the destionation of the copy</param>
void Assign(Country sourceC, Country* destinationC);

/// <summary>
/// For printing the format of a Country
/// </summary>
/// <param name="Country">The Country obj</param>
/// <returns>The country format ready for printing</returns>
char* ToString(Country country);

/// <summary>
/// A function to verify the params of a Country introduced by the user
/// </summary>
/// <param name="name">The name of the Country</param>
/// <param name="continent">The continent of the Country</param>
/// <param name="population">The population of the Country</param>
/// <returns>1 if the params are valid, 0 otherwise</returns>
int ValidParameters(char name[], char continent[], double populatoin);

/// <summary>
/// Verification of the name
/// </summary>
/// <param name="name">The name of the Country</param>
/// <returns>1 if the name is valid, 0 otherwise</returns>
int ValidName(char name[]);

/// <summary>
/// Verification of the continent
/// </summary>
/// <param name="continent">The continent of the Country</param>
/// <returns>1 if the concentration is valid, 0 otherwise</returns>
int ValidContinent(char continent[]);

/// <summary>
/// Verification of the population
/// </summary>
/// <param name="population">The population of the Country</param>
/// <returns>1 if the quantity is valid, 0 otherwise</returns>
int ValidPopulation(double population);

/// <summary>
/// Tests
/// </summary>
void RunAllTestsCountry();
void TestGettersandSetters();
void TestAssign();
void TestValidators();
