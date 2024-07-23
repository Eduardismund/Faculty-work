#include <stdlib.h>
#include <stdio.h>
#include "Operation.h"
Operation *createOperation(int typeOfOperation, Estate *Estate1, Estate *Estate2)
{
    Operation *operation = (Operation *)malloc(sizeof(Operation));
    operation->typeOfOperation = typeOfOperation;
    operation->Estate1 = createEstate(Estate1->type, Estate1->address, Estate1->surface, Estate1->price);
    operation->Estate2 = NULL;
    if (Estate2)
        operation->Estate2 = createEstate(Estate2->type, Estate2->address, Estate2->surface, Estate2->price);
    return operation;
}

Estate *getEstate1(Operation *operation)
{
    return operation->Estate1;
}

Estate *getEstate2(Operation *operation)
{
    return operation->Estate2;
}

int getTypeOfOperation(Operation *operation)
{
    return operation->typeOfOperation;
}

void destroyOperation(Operation *operation)
{
    destroyEstate(getEstate1(operation));
    if (getEstate2(operation))
        destroyEstate(getEstate2(operation));
    free(operation);
}