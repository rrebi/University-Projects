#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Console* CreateConsole(Service* service, UndoService* undoService)
{
	Console* console = (Console*)malloc(sizeof(Console));
	
	if (console == NULL)
		return NULL;

	console->service = service;
	console->undoService = undoService;
	return console;
}

void DestroyConsole(Console* console)
{
	free(console);
}

void PrintMenuUi(Console* console)
{
	printf("\n");
	printf("1.Add a new country\n");
	printf("2.Remove country\n");
	printf("3.Update country\n");
	printf("4.Filter country\n");
	printf("5.Print all countries\n");
	printf("6.Print only those countries that have the population greater than x\n");
	printf("u.Undo the last action\n");
	printf("r.Redo the last action\n");
	printf("0.Exit\n");
	printf("\n");
}

void PrintCountryUi(Console* console)
{
	char ch[256];
	for (size_t i = 0; i < GetLength(console->service->repo); ++i)
	{
		strcpy(ch, ToString(GetElemOnPos(console->service->repo, i)));
		printf("%s\n", ch);

	}
}
void AddCountryUi(Console* console)
{
	char name[100], continent[100];
	double population;
	printf("Enter a country name:\n");
	int count = scanf("%s", name);
	if (count == 0)
	{
		printf("Invalid name!\n");
		return;
	}

	printf("Enter country's continent:\n");
	int count1 = scanf("%s", &continent);
	if (count1 == 0)
	{
		printf("Invalid continent!\n");
		return;
	}

	printf("Enter country's population:\n");
	int count2;
	count2 = scanf("%lf", &population);
	if (count2 == 0)
	{
		printf("Invalid population!\n");
		return;
	}


	int result = AddCountryService(console->service, name, continent, population);
	if (result == 1)
	{
		printf("Invalid input or Country already exists!\n");
		return;
	}

	Repository repoCopy = DuplicateRepo(*console->service->repo);
	AddEntry(console->undoService, repoCopy);
}

void RemoveCountryUi(Console* console)
{
	char name[101];
	char continent[101];
	printf("Enter the name of the country you want to remove:\n");
	int count = scanf("%s", name);
	printf("Enter the continent of the country you want to remove:\n");
	int count2 = scanf("%s", &continent);

	int result = RemoveCountryService(console->service, name, continent);
	if (result == 1)
	{
		printf("Invalid input!\n");
		return;
	}
	Repository repoCopy = DuplicateRepo(*console->service->repo);
	AddEntry(console->undoService, repoCopy);
}

void UpdateCountryUi(Console* console)
{
	printf("What would you like to modify? Enter P for Population or M for Migration\n");
	char myString[100];
	int count = scanf("%s", myString);
	strcat(myString, "\0");
	if (strlen(myString) != 1 ||
		(myString[0] != 'P' && myString[0] != 'p' &&
			myString[0] != 'M' && myString[0] != 'm'))
	{
		printf("Invalid command!\n");
		return;
	}

	switch (myString[0])
	{
		case 'P':
		case 'p':
		{
	//if(strcmp(myString, 'P') == 0 || strcmp(myString, 'p') == 0)
	//{
		char name[50], continent[50];
		double population, newPopulation;
		printf("Enter the name of the country you want to update:\n");
		int count = scanf("%s", name);
		printf("Enter the continent of the country you want to update:\n");
		int count2 = scanf("%s", continent);
		printf("Enter the population of the country:\n");
		int count3 = scanf("%lf", &population);
		printf("Enter the new population of the country:\n");
		int count4 = scanf("%lf", &newPopulation);

		int result = UpdatePopulationService(console->service, name, population, newPopulation);
		if (result == 1)
		{
			printf("Country not found!\n");
			return NULL;
		}
		Repository repoCopy = DuplicateRepo(*console->service->repo);
		AddEntry(console->undoService, repoCopy);
	}
		
		case 'M':
		case 'm':
	//else
	{
		char name[50], newName[50];
		double migrating;
		printf("Enter the name of the country from where people leave:\n");
		int count = scanf("%s", name);
		printf("Enter the name of the country they migrate to:\n");
		int count2 = scanf("%s", newName);
		printf("Enter the number of people migrating:\n");
		int count3 = scanf("%lf", &migrating);
		int result = Migration(console->service, name, migrating, newName);
		if (result == 1)
		{
			printf("Country not found!\n");
			return NULL;
		}
		Repository repoCopy = DuplicateRepo(*console->service->repo);
		AddEntry(console->undoService, repoCopy);
		
	}


		
	default:
		break;
	}
}

void FilterCountryUi(Console* console)
{
	char searchString[50];
	printf("Enter a substring for searching!:\n");
	gets(searchString);
	fgets(searchString, 50, stdin);
	searchString[strcspn(searchString, "\n")] = 0;

	Country result[100];
	size_t size;
	if (strcmp(searchString, "NULL") == 0)
	{
		char ch[256];
		for (size_t i = 0; i < GetLength(console->service->repo); ++i)
		{
			strcpy(ch, ToString(GetElemOnPos(console->service->repo, i)));
			printf("%s\n", ch);

		}
		
	}
	else {
		GetCountryContainingString(console->service, searchString, result, &size);
		char countryString[256];

		SortByName(result, size);
		for (size_t i = 0; i < size; ++i)
		{
			strcpy(countryString, ToString(result[i]));
			printf("%s\n", countryString);
		}
	}

}

void PrintCountryByPopulationUi(Console* console)
{
	char searchString[50];
	printf("Enter a continent for searching!:\n");
	gets(searchString);
	fgets(searchString, 50, stdin);
	searchString[strcspn(searchString, "\n")] = 0;

	double population;
	printf("Enter a population to search country grater than:\n");
	int c = scanf("%lf", &population);

	Country result[100];
	size_t size;
	
	if (strcmp(searchString, "NULL") == 0)
	{
		GetCountryByPopulation(console->service, result, &size, population);
		char countryString[256];

		SortByPopulation(result, size);
		for (size_t i = 0; i < size; ++i)
		{
			strcpy(countryString, ToString(result[i]));
			printf("%s\n", countryString);
		}
	}
	else
	{
		GetCountryByContinentPopulation(console->service, result, &size, searchString, population);
		char countryString[256];

		SortByPopulation(result, size);
		for (size_t i = 0; i < size; ++i)
		{
			strcpy(countryString, ToString(result[i]));
			printf("%s\n", countryString);
		}
	}
}

void MainLoop(Console* console)
{
	int ok = 0;
	char command[10];

	while (!ok)
	{
		PrintMenuUi(console);
		printf("Enter command:\n");
		int count = scanf("%s", command);
		strcat(command, "\0");

		if (strlen(command) != 1)
			printf("Invalid command! Please try again!");
		else
		{
			switch (command[0])
			{
			case '1':
			{
				AddCountryUi(console);
				break;
			}
			case '2':
			{
				RemoveCountryUi(console);
				break;
			}
			case '3':
			{
				UpdateCountryUi(console);
				break;
			}
			case '4':
			{
				FilterCountryUi(console);
				break;
			}
			case '5':
			{
				PrintCountryUi(console);
				break;
			}
			case '6':
			{
				PrintCountryByPopulationUi(console);
				break;
			}
			case '0':
			{
				ok = 1;
				break;
			}
			case 'u':
			{
				int res = UndoAction(console->undoService, console->service->repo);
				if (res == 1)
				{
					printf("No more undos!\n");
				}
				break;
			}
			case 'r':
			{
				int res = RedoAction(console->undoService, console->service->repo);
				if (res == 1)
				{
					printf("No more redos!\n");
				}
				break;
			}
			default:
			{
				printf("Invalid command!");
				break;
			}
			}

		}
	}
}




