#include "Array.h"

void MakeArray(void* arrayPtr[], int arraySize) {

	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	for (int i = 0; i < arraySize; i++)
		arrayPtr[i] = NULL;
}

void AddToArray(void* arrayPtr[], void* pointer, int arraySize) {
	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	// From here on out, the function finds a null spot to write in.
	// NOTE: This is the *first* null spot.

	int i; 
	for (i = 0; i < arraySize; i++) {
		if (arrayPtr[i] == NULL)
			break;
	}

	arrayPtr[i] = pointer;
	#ifdef DEBUG
		fprintf(stderr, "Place in array: %d\n", i);
	#endif
}

int FindPointerArray(void* arrayPtr[], void* pointer, int arraySize) {
	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	// Finds if a pointer is in an array, and what spot it's in.

	int i = 0;
	while (arrayPtr[i] != pointer)
		i++;
	return i;
}