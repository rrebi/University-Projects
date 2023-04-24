#pragma once
#include "Service.h"
#include "UndoService.h"

typedef struct
{
	Service* service;
	UndoService* undoService;
}Console;


/// <summary>
/// Constructor for the console
/// </summary>
/// <param name="service">The service contained by the console</param>
/// <param name="undoService">The undo service contained by the console</param>
/// <returns>The console obj</returns>
Console* CreateConsole(Service* service, UndoService* undoService);

/// <summary>
/// Destructor for the console
/// </summary>
/// <param name="console">The console to be destroyed</param>
void DestroyConsole(Console* console);

/// <summary>
/// The console based menu
/// </summary>
/// <param name="console">The console</param>
void PrintMenuUi(Console* console);

/// <summary>
/// Print the list of medicines
/// </summary>
/// <param name="console">The console</param>
void PrintCountryUi(Console* console);

/// <summary>
/// The Country containing a string
/// </summary>
/// <param name="console">The console</param>
void FilterCountryUi(Console* console);

/// <summary>
/// Add Country to the list
/// </summary>
/// <param name="console">The console</param>
void AddCountryUi(Console* console);

/// <summary>
/// Remove Country from the list
/// </summary>
/// <param name="console">The console</param>
void RemoveCountryUi(Console* console);

/// <summary>
/// Update Country from the list
/// </summary>
/// <param name="console">The console</param>
void UpdateCountryUi(Console* console);

/// <summary>
/// The menu
/// </summary>
/// <param name="console">The console</param>
void MainLoop(Console* console);
