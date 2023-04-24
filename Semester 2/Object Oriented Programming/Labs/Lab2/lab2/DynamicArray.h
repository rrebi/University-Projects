#pragma once

#include "country.h"
#include <stddef.h>

typedef Country TElement;

typedef struct
{
	TElement* elements;
	size_t length;
	size_t maxLength;

}DynamicArray;

/// <summary>
/// Constructor fo a DynamicArray object
/// </summary>
/// <param name="maxLength">The maximum size of the dynamic array</param>
/// <returns>The new Dynamic array object</returns>
DynamicArray* CreateArray(size_t maxLength);

/// <summary>
/// Copy constructor for a dynamic array
/// </summary>
/// <param name="source">the array to be copied</param>
/// <param name="destination">a copy of the given dynamic array</param>

void DuplicateArray(DynamicArray source, DynamicArray* destination);

/// <summary>
/// Destructor for a dynamic array
/// </summary>
/// <param name="array">The array to be destroyed</param>
void DestroyArray(DynamicArray* array);

/// <summary>
/// Adds a new element to the Dynamic array
/// </summary>
/// <param name="array">the dynamic array where to add a new elem</param>
/// <param name="newElem">the elem to be added</param>
void AddElement(DynamicArray* array, TElement newElem);

/// <summary>
/// Removes an elem of the dynamic array
/// </summary>
/// <param name="array">the dynamic array from where an elem is removed</param>
/// <param name="position">the pos of the elem to be removed</param>
void RemoveElement(DynamicArray* array, size_t position);

/// <summary>
/// Copy of the constructor
/// </summary>
/// <param name="sourceArray">the dynamic array to be copied</param>
/// <param name="destination">the destination of the copy</param>
void Copy(DynamicArray sourceArray, DynamicArray* destination);