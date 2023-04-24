#include "Repository.h"
#include <stdlib.h>
#include <assert.h>

Repository* CreateRepo(size_t maxLength)
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));

	if (repo == NULL)
		return NULL;

	repo->array = CreateArray(maxLength);
    if (repo->array == NULL)
        return NULL;

    return repo;
}

Repository DuplicateRepo(Repository source)
{
    Repository newRepo;

    DynamicArray* newArray = CreateArray(1);
    DuplicateArray(*source.array, newArray);

    newRepo.array = newArray;
    if (newRepo.array == NULL)
    {
        newRepo.array->maxLength = 0;
        newRepo.array->length = 0;
    }

    return newRepo;
}

void DestroyRepo(Repository* repo)
{
    if (repo == NULL)
        return NULL;

    DestroyArray(repo->array);
    repo->array = NULL;

    free(repo);
}

void AddCountry(Repository* repo, Country country)
{
    AddElement(repo->array, country);

}

void RemoveCountry(Repository* repo, size_t position)
{
    RemoveElement(repo->array, position);
}

void UpdatePopulation(Repository* repo, rsize_t position, double newPopulation)
{
    SetPopulation(&repo->array->elements[position], newPopulation);
}


void InitRepo(Repository* repo)
{
    AddCountry(repo, createCountry("Switzerland", "Europe", 50));
    AddCountry(repo, createCountry("Austria", "Europe", 30));
    AddCountry(repo, createCountry("Germany", "Europe", 120));
    AddCountry(repo, createCountry("Itay", "Europe", 20));
    AddCountry(repo, createCountry("France", "Europe", 70));
    AddCountry(repo, createCountry("Norway", "Europe", 40));
    AddCountry(repo, createCountry("SSS", "USA", 10));
    AddCountry(repo, createCountry("UUU", "USA", 50));
    AddCountry(repo, createCountry("AAA", "Asia", 20));
}

void CopyRepo(Repository sourceRepo, Repository* destinationRepo)
{
    Copy(*sourceRepo.array, destinationRepo->array);
}

size_t GetLength(Repository* repo)
{
    return repo->array->length;
}

Country GetElemOnPos(Repository* repo, size_t position)
{
    if (position > repo->array->length)
        return createCountry("Invalid", "Invalid", 0);
    return repo->array->elements[position];
}



void RunAllTestsRepo()
{
   TestAdd();
   TestRemove();
   TestUpdate();
   TestGetLength();
   TestGetElemOnPos();
   TestCopy();
}

void TestAdd()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);
    assert(repo->array->length == 1);
    assert(strcmp(repo->array->elements[0].name, "AA") == 0);
    assert(strcmp(repo->array->elements[0].continent, "A") == 0);
    assert((double)repo->array->elements[0].population == (double)(34));

    DestroyRepo(repo);
}

void TestRemove()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);
    assert(repo->array->length != 0);
    assert(strcmp(repo->array->elements[0].name, "AA") == 0);
    assert(strcmp(repo->array->elements[0].continent, "A") == 0);
    assert((double)repo->array->elements[0].population == (double)(34));

    Country cc = createCountry("AA", "A", 34);
    AddCountry(repo, cc);
    assert(repo->array->length == 2);
    RemoveCountry(repo, 0);
    assert(repo->array->length == 1);
    assert(strcmp(repo->array->elements[0].name, "AA") == 0);

    DestroyRepo(repo);
}

void TestUpdate()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);
    assert((double)repo->array->elements[0].population == (double)(34));

    UpdatePopulation(repo, 0, 100);
    assert((double)repo->array->elements[0].population == (double)(100));

    DestroyRepo(repo);
}

void TestGetLength()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);
    assert(GetLength(repo) == 1);

    Country cc = createCountry("AA", "A", 34);
    AddCountry(repo, cc);
    assert(GetLength(repo) != 0);

    DestroyRepo(repo);
}

void TestGetElemOnPos()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);
    assert(strcmp(GetElemOnPos(repo, 0).name, "AA") == 0);
    assert((double)GetElemOnPos(repo, 0).population == (double)34);

    DestroyRepo(repo);
}

void TestCopy()
{
    Repository* repo = CreateRepo(1);
    Country c = createCountry("AA", "A", 34);
    AddCountry(repo, c);

    Repository repoCopy = DuplicateRepo(*repo);
    assert(repoCopy.array->length == repo->array->length);
    assert(repoCopy.array->maxLength == repo->array->maxLength);

    for (size_t i = 0; i < repo->array->length; ++i)
    {
        assert(strcmp(repo->array->elements[i].name, repoCopy.array->elements[i].name) == 0);
        assert(strcmp(repo->array->elements[i].continent, repoCopy.array->elements[i].continent) == 0);
        assert(repo->array->elements[i].population == repoCopy.array->elements[i].population);
    }

    DestroyRepo(repo);
    DestroyArray(repoCopy.array);
}