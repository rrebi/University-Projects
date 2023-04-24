#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray* CreateArray(size_t maxLength)
{
	DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (array == NULL)
		return NULL;

	array->maxLength = maxLength;
	array->length = 0;
	array->elements = (TElement*)malloc(maxLength * sizeof(TElement));

    if (array->elements == NULL)
    {
        free(array);
        return NULL;
    }

	return array;

}

void DuplicateArray(DynamicArray source, DynamicArray* destination)
{
    TElement* ptr = realloc(destination->elements, source.maxLength * sizeof(TElement));
    destination->elements = ptr;
    if (destination->elements == NULL)
    {
        destination->maxLength = 0;
        destination->length = 0;
    }

    Copy(source, destination);
}

void DestroyArray(DynamicArray* array)
{
    if (array == NULL)
        return NULL;

    free(array->elements);
    array->elements = NULL;

    free(array);
}

void ReallocateArray(DynamicArray* array, size_t newMaxLength)
{
    if (array->elements == NULL)
        return;
    TElement* elemPtr = array->elements;
    TElement* ptr = realloc(array->elements, newMaxLength * sizeof(TElement));
    array->maxLength = newMaxLength;
    array->elements = (TElement*)ptr;
}

void AddElement(DynamicArray* array, TElement newElement)
{
    if (array == NULL)
        return;
    if (array->elements == NULL)
        return;

    if (array->length == array->maxLength)
        ReallocateArray(array, 2 * array->length);

    array->elements[array->length++] = newElement;
}

void RemoveElement(DynamicArray* array, size_t position)
{
    if (array == NULL)
        return;
    if (array->elements == NULL)
        return;

    if (position >= array->length)
        return;

    for (size_t i = position + 1; i < array->length; ++i)
        array->elements[i-1] = array->elements[i];

    array->length--;
}

void Copy(DynamicArray sourceArray, DynamicArray* destinationArray)
{
    destinationArray->maxLength = sourceArray.maxLength;
    destinationArray->length = sourceArray.length;

    for (size_t i = 0; i < sourceArray.length; ++i)
        Assign(sourceArray.elements[i], &destinationArray->elements[i]);
}

