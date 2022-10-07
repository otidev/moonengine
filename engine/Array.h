#ifndef MOON_ENGINE_ARRAY_H
#define MOON_ENGINE_ARRAY_H

#define IsSizeOf(type, array) sizeof(*(type*)array) == sizeof(type)

#include "Include.h"

// Makes an array
void MakeArray(void* arrayPtr[], int arraySize);

// Adds to an array
void AddToArray(void* arrayPtr[], void* pointer, int arraySize);

// Finds a pointer in an array
int FindPointerArray(void* arrayPtr[], void* pointer, int arraySize);

// NOTE: Freeing of arrays defined by array type headers

#endif