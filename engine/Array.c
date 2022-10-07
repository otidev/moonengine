#include "Array.h"

void MakeArray(void* arrayPtr[], int arraySize) {
	int i;

	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	for (i = 0; i < arraySize; i++)
		arrayPtr[i] = NULL;
}

void AddToArray(void* arrayPtr[], void* pointer, int arraySize) {

	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;
	while (arrayPtr[i] != NULL)
		i++;
	arrayPtr[i] = pointer;
	#ifdef DEBUG
		fprintf(stderr, "Place in array: %d\n", i);
	#endif
}

int FindPointerArray(void* arrayPtr[], void* pointer, int arraySize) {
	if (arraySize == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;
	while (arrayPtr[i] != pointer)
		i++;
	return i;
}