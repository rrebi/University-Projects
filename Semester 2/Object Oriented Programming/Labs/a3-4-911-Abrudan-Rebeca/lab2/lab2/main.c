#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include "ui.h"

int main()
{
    
    RunAllTestsCountry();
    RunAllTestsRepo();
    RunAllTestsService();
    
    Repository* repository = CreateRepo(10);
    Service* service = CreateService(repository);
    UndoService* undoservice = CreateUndoService(10);
    Console* console = CreateConsole(service, undoservice);

    InitRepo(repository);
    Repository repoCopy = DuplicateRepo(*repository);
    AddEntry(undoservice, repoCopy);

    MainLoop(console);

    DestroyConsole(console);
    DestroyService(service);
    DestroyUndoService(undoservice);
    DestroyRepo(repository);

    int c= _CrtDumpMemoryLeaks();
    printf("%d", c);
    return 0;
}

