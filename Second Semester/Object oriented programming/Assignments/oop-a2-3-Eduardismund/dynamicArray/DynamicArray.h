#pragma once
#include "../domain/RealEstateAgency.h"


// We create a type that allows working with any data type regarding elements stored in Dynamic array,
// not a specific one like char or int
typedef void *TElem;

// Function pointer type for destroying elements
typedef void (*DestroyElementFunctionPointer)(TElem);

// Structure representing a dynamic array
typedef struct{
    //we create a pointer to the vector of elements
    TElem *elems;
    //the actual size and the capacity(which could be resized later on if needed) of type int
    int size, capacity;
    //function pointer type, pointing to a function responsible for freeing memory associated with individual elements
    DestroyElementFunctionPointer destroyElementFunctionPointer;
}DynamicArray;

DynamicArray *createDynamicArray(int, DestroyElementFunctionPointer);
void resizeDynamicArray(DynamicArray*);
void destroyDynamicArray(DynamicArray *);
void setLengthOfDynamicArray(DynamicArray *, int);
TElem *getElements(DynamicArray *);
TElem *getElementOnIndex(DynamicArray *, int);
void addElementToDA(DynamicArray *, TElem);
void deleteElementFromDA(DynamicArray *, int);
void updateElementAnIndex(DynamicArray *, int, TElem);
int getLengthOfDynamicArray(DynamicArray *);
int getCapacityOfDynamicArray(DynamicArray *);
void swapElementsOnDynamicArray(DynamicArray *, int, int);
DestroyElementFunctionPointer getDestroyElementFunctionPointer(DynamicArray *);
DynamicArray *copyDynamicArrayOfEstates(DynamicArray *);