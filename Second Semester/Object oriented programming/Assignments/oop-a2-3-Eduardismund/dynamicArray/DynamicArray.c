#include "DynamicArray.h"
#include "Operation.h"
#include <stdlib.h>
#include <stdio.h>

// Creates a dynamic array with the given capacity and destroy function
// destroyElementFunctionPointer: Pointer to a function that destroys elements in the array
DynamicArray *createDynamicArray(int capacity, DestroyElementFunctionPointer destroyElementFunctionPointer)
{
    DynamicArray *dynamicArrayAgency = (DynamicArray*) malloc(sizeof(DynamicArray));
    if (dynamicArrayAgency == NULL)
        return NULL;
    dynamicArrayAgency->elems = (TElem*) malloc(capacity * sizeof(TElem));
    dynamicArrayAgency->size = 0;
    dynamicArrayAgency->capacity = capacity;
    dynamicArrayAgency->destroyElementFunctionPointer = destroyElementFunctionPointer;
    return dynamicArrayAgency;
}
int getLengthOfDynamicArray(DynamicArray *dynamicArray)
{
    return dynamicArray->size;
}

int getCapacityOfDynamicArray(DynamicArray *dynamicArray)
{
    return dynamicArray->capacity;
}

TElem *getElements(DynamicArray *dynamicArray)
{
    return dynamicArray->elems;
}
DestroyElementFunctionPointer getDestroyElementFunctionPointer(DynamicArray *dynamicArray)
{
    return dynamicArray->destroyElementFunctionPointer;
}
void setLengthOfDynamicArray(DynamicArray *dynamicArray, int length)
{
    dynamicArray->size = length;
}
// Deallocates memory used by the dynamic array and its elements
void destroyDynamicArray(DynamicArray* da){
    for (int i = 0; i < getLengthOfDynamicArray(da); i++) {
        if (da->elems[i])
            da->destroyElementFunctionPointer(da->elems[i]);
    }
    free(da->elems);
    free(da);
}

// Retrieves the element at the specified position in the dynamic array
TElem *getElementOnIndex(DynamicArray *dynamicArray, int position) {
    if (position < 0 || position >= dynamicArray->size) {
        return NULL;
    }
    return dynamicArray->elems[position];
}

// Resizes the capacity of the dynamic array by doubling it
void resizeDynamicArray(DynamicArray *dynamicArray) {
    TElem *tempElems = dynamicArray->elems; // Store the original pointer
    dynamicArray->capacity += 1;
    TElem *newElems = realloc(tempElems, dynamicArray->capacity * sizeof(TElem));
    if (newElems == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Error: Failed to resize dynamic array. Memory allocation failed.\n");
        // Since realloc failed, do not lose the reference to the original buffer
        return;
    }
    // Update the pointer with the new memory block
    dynamicArray->elems = newElems;
}

// Updates the element at the specified position in the dynamic array with a new element
void updateElementAnIndex(DynamicArray *dynamicArray, int position, TElem element) {
    if (position < 0 || position >= dynamicArray->size) {
        return;
    }
    DestroyElementFunctionPointer destroyElementFunctionPointer = getDestroyElementFunctionPointer(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    destroyElementFunctionPointer(elements[position]);
    elements[position] = element;
}
// Swaps the elements at the specified positions in the dynamic array
void swapElementsOnDynamicArray(DynamicArray *dynamicArray, int position1, int position2) {
    int length = getLengthOfDynamicArray(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    if (position1 < 0 || position1 >= length || position2 < 0 || position2 >= length) {
        return;
    }
    TElem aux = elements[position1];
    elements[position1] = elements[position2];
    elements[position2] = aux;
}

// Adds a new element to the end of the dynamic array
void addElementToDA(DynamicArray *dynamicArray, TElem element) {
    int length = getLengthOfDynamicArray(dynamicArray);
    int capacity = getCapacityOfDynamicArray(dynamicArray);
    TElem *elements = getElements(dynamicArray);

    if (length == capacity)
        resizeDynamicArray(dynamicArray);

    elements[length] = element;
    dynamicArray->size += 1;
}

// Deletes the element at the specified position in the dynamic array
void deleteElementFromDA(DynamicArray *dynamicArray, int position) {
    DestroyElementFunctionPointer destroyElementFunctionPointer = getDestroyElementFunctionPointer(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    int length = getLengthOfDynamicArray(dynamicArray);
    if (position < 0 || position >= length)
        return;

    destroyElementFunctionPointer(elements[position]);
    for (int i = position; i < length - 1; ++i)
        elements[i] = elements[i + 1];

    elements[length - 1] = NULL;
    setLengthOfDynamicArray(dynamicArray, length - 1);
}

DynamicArray *copyDynamicArrayOfEstates(DynamicArray *dynamicArray)
{
    int length = getLengthOfDynamicArray(dynamicArray);
    DynamicArray *copy = createDynamicArray(length, destroyEstate);
    for (int i = 0; i < length; i++)
    {
        TElem *element = getElementOnIndex(dynamicArray, i);
        addElementToDA(copy, copyEstate((Estate *)element));
    }
    return copy;
}