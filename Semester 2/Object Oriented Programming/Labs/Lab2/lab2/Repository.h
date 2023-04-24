#pragma once

#include "DynamicArray.h"
#include "country.h"
#include <stddef.h>

typedef struct
{
	DynamicArray* array;

}Repository;

/// <summary>
/// Constructor for the repo
/// </summary>
/// <param name="maxLength">The maximum size of the repo</param>
/// <returns>The created repo</returns>
Repository* CreateRepo(size_t maxLength);

/// <summary>
/// Copy of the repo constructor
/// </summary>
/// <param name="source">The repo to be copied</param>
/// <returns>the duplicated repo</returns>
Repository DuplicateRepo(Repository source);

/// <summary>
/// Destructor for the repo obj
/// </summary>
/// <param name="repo">the repo to be destroyed</param>
void DestroyRepo(Repository* repo);

/// <summary>
/// Add a Country object to the repo
/// </summary>
/// <param name="repo">The repo where to add the object</param>
/// <param name="country">The Country to be added to the repo</param>
void AddCountry(Repository* repo, Country country);

/// <summary>
/// Remove a Country from the repo 
/// </summary>
/// <param name="repo">The repo where to remove a Country from</param>
/// <param name="position">The position of the Country to be removed</param>
void RemoveCountry(Repository* repo, size_t position);

/// <summary>
/// Update the quantity of a Country
/// </summary>
/// <param name="repo">The repo where to make the update</param>
/// <param name="position">The position of the element to be updated</param>
/// <param name="newPopulation">The new population to be updated</param>
void UpdatePopulation(Repository* repo, rsize_t position, double newPopulation);

/// <summary>
/// Copy of the repo
/// </summary>
/// <param name="sourceRepo">the repo to be copied</param>
/// <param name="destinationRepo">te destination of the copy</param>
void CopyRepo(Repository sourceRepo, Repository* destinationRepo);

/// <summary>
/// 10 items to be already introduced to the repo
/// </summary>
/// <param name="repo">The repo where to introduced the items</param>
void InitRepo(Repository* repo);

/// <summary>
/// Getter for the length of the repo
/// </summary>
/// <param name="repo">The repo to get the length of</param>
/// <returns>The size of the repo</returns>
size_t GetLength(Repository* repo);

/// <summary>
/// Getter of a medicine from the repo
/// </summary>
/// <param name="repo">The repo to look for a medicine</param>
/// <param name="position">The position of the medicine to get</param>
/// <returns>The desired Country object</returns>
Country GetElemOnPos(Repository* repo, size_t position);

/// <summary>
/// Tests
/// </summary>
void RunAllTestsRepo();
void TestAdd();
void TestRemove();
void TestUpdate();
void TestGetLength();
void TestGetElemOnPos();
void TestCopy();
