#include "UndoService.h"
#include <stdlib.h>
#include <assert.h>

UndoService* CreateUndoService(size_t maxSize)
{
	UndoService* service = (UndoService*)malloc(sizeof(UndoService));
	if (service == NULL) return NULL;

	service->maxSize = maxSize;
	service->currentIndex = -1;
	service->currentSize = 0;
	service->maxAttainedSize = 0;

	service->history = (Repository*)malloc(maxSize * sizeof(Repository));
	if (service->history == NULL) return NULL;

	return service;
}

void DestroyUndoService(UndoService* undoService)
{
	if (undoService == NULL) return NULL;

	for (size_t i = 0; i < undoService->currentSize; ++i)
		DestroyArray(undoService->history[i].array);

	free(undoService->history);
	undoService->history == NULL;

	free(undoService);
}

void ReallocateHistory(UndoService* undoService, size_t newMaxSize)
{
	if (undoService->history == NULL) return NULL;
	Repository* elemPtr = undoService->history;
	Repository* ptr = realloc(undoService->history, newMaxSize);
	undoService->maxSize = newMaxSize;
	undoService->history = (Repository*)ptr;
}

void AddEntry(UndoService* undoService, Repository newEntry)
{
	if (undoService == NULL) return;
	if (undoService->history == NULL) return;

	undoService->currentIndex++;
	undoService->currentSize++;
	if (undoService->currentIndex + 1 != undoService->currentSize)
	{
		for (size_t i = undoService->currentIndex; i < undoService->currentSize - 1; ++i)
			DestroyArray(undoService->history[i].array);

		undoService->history[undoService->currentIndex] = newEntry;
		undoService->currentSize = undoService->currentIndex + 1;
	}
	else {
		if (undoService->currentSize == undoService->maxSize)
			ReallocateHistory(undoService, 2 * undoService->currentSize);

		undoService->history[undoService->currentIndex] = newEntry;
	}
}

void RemoveEntry(UndoService* undoService, size_t position)
{
	if (undoService == NULL) return;
	if (undoService->history == NULL) return;

	if (position > undoService->currentSize) return;

	for (size_t i = position; i < undoService->currentSize - 1; ++i)
		undoService->history[i] = undoService->history[i + 1];

	undoService->currentSize--;
	undoService->currentIndex--;
}

int UndoAction(UndoService* undoService, Repository* repo)
{
	if (undoService->currentIndex == 0) return 1;
	CopyRepo(undoService->history[--undoService->currentIndex], repo);
	return 0;
}

int RedoAction(UndoService* undoService, Repository* repo)
{
	if (undoService->currentIndex == undoService->currentSize - 1)
		return 1;
	undoService->currentIndex++;
	CopyRepo(undoService->history[undoService->currentIndex], repo);
	return 0;
}
void RunAllTestsUndoService()
{
	TestCreateDestroyUndoService();
	TestAddUndoService();
	TestRemoveUndoService();
	TestUndo();
	TestRedo();
}

void TestCreateDestroyUndoService()
{
	UndoService* undoService = CreateUndoService(12);
	assert(undoService != NULL);
	assert(undoService->maxSize == 12);
	assert(undoService->currentIndex == -1);
	assert(undoService->currentSize == 0);

	DestroyUndoService(undoService);
}

void TestAddUndoService()
{
	UndoService* undoService = CreateUndoService(1);
	Repository* repo1 = CreateRepo(1);
	Repository* repo2 = CreateRepo(1);
	Repository* repo3 = CreateRepo(1);
	Repository* repo4 = CreateRepo(1);


	Country m1 = createCountry("AA", "A", 100);
	AddCountry(repo1, m1);

	Country m2 = createCountry("AAAA", "A", 100);
	AddCountry(repo1, m2);

	Country m3 = createCountry("ABA", "A", 100);
	AddCountry(repo2, m3);

	AddEntry(undoService, *repo1);
	assert(undoService->currentSize == 1);
	assert(undoService->maxSize == 2);

	AddEntry(undoService, *repo2);
	assert(undoService->currentIndex == 1);
	assert(undoService->currentSize == 2);
	assert(undoService->maxSize == 4);

	AddEntry(undoService, *repo3);
	undoService->currentIndex = 0;
	AddEntry(undoService, *repo4);
	assert(undoService->currentIndex == 1);
	assert(undoService->currentSize == 2);
	assert(undoService->maxSize == 4);

	DestroyRepo(repo1);
	free(repo2);
	free(repo3);
	DestroyRepo(repo4);
	free(undoService->history);
	free(undoService);
}

void TestRemoveUndoService()
{
	UndoService* undoService = CreateUndoService(1);
	Repository* repo1 = CreateRepo(1);
	Repository* repo2 = CreateRepo(1);

	Country m1 = createCountry("AA", "A", 100);
	AddCountry(repo1, m1);

	Country m2 = createCountry("AAAA", "A", 100);
	AddCountry(repo1, m2);

	Country m3 = createCountry("ABA", "A", 100);
	AddCountry(repo2, m3);

	AddEntry(undoService, *repo1);

	AddEntry(undoService, *repo2);
	assert(undoService->currentIndex == 1);
	assert(undoService->currentSize == 2);
	assert(undoService->maxSize == 4);

	RemoveEntry(undoService, 0);
	assert(undoService->currentIndex == 0);
	assert(undoService->currentSize == 1);
	assert(undoService->maxSize == 4);

	DestroyRepo(repo1);
	DestroyRepo(repo2);
	free(undoService->history);
	free(undoService);
}

void TestUndo()
{
	UndoService* undoService = CreateUndoService(1);
	Repository* repo1 = CreateRepo(1);
	Repository* repo2 = CreateRepo(1);
	Repository* repo3 = CreateRepo(4);

	Country m1 = createCountry("AA", "A", 100);
	AddCountry(repo1, m1);

	Country m2 = createCountry("AAAA", "A", 100);
	AddCountry(repo1, m2);

	Country m3 = createCountry("ABA", "A", 100);
	AddCountry(repo2, m3);

	AddEntry(undoService, *repo1);

	AddEntry(undoService, *repo2);

	UndoAction(undoService, repo3);
	assert(undoService->currentIndex == 0);
	assert(repo3->array->length == 2);
	assert((double)repo3->array->elements[0].population == (double)repo1->array->elements[0].population);

	DestroyRepo(repo1);
	DestroyRepo(repo2);
	DestroyRepo(repo3);
	free(undoService->history);
	free(undoService);
}

void TestRedo()
{
	UndoService* undoService = CreateUndoService(1);
	Repository* repo1 = CreateRepo(1);
	Repository* repo2 = CreateRepo(1);
	Repository* repo3 = CreateRepo(4);

	Country m1 = createCountry("AA", "A", 100);
	AddCountry(repo1, m1);

	Country m2 = createCountry("AAAA", "A", 100);
	AddCountry(repo1, m2);

	Country m3 = createCountry("ABA", "A", 100);
	AddCountry(repo2, m3);

	AddEntry(undoService, *repo1);

	AddEntry(undoService, *repo2);

	UndoAction(undoService, repo3);
	assert(undoService->currentIndex == 0);
	assert(repo3->array->length == 2);
	assert((double)repo3->array->elements[0].population == (double)repo1->array->elements[0].population);

	RedoAction(undoService, repo3);
	assert(undoService->currentIndex == 1);
	assert(repo3->array->length == 1);
	assert((double)repo3->array->elements[0].population == (double)repo2->array->elements[0].population);

	DestroyRepo(repo1);
	DestroyRepo(repo2);
	DestroyRepo(repo3);
	free(undoService->history);
	free(undoService);
}


