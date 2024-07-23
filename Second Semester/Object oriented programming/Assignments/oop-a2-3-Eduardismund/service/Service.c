#include "Service.h"
#include "../dynamicArray/DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void generateEntries(Service *service){

    Estate *estate = createEstate("house", "123 Oak Street", 100, 2000);
    addEstateService(service, estate);
    Estate *estate1 = createEstate("apartment", "78 Elm Street", 50, 500);
    addEstateService(service, estate1);
    Estate *estate3 = createEstate("penthouse", "60 Pine Road", 200, 10000);
    addEstateService(service, estate3);
    Estate *estate4 = createEstate("house", "15 Spruce Boulevard", 150, 1500);
    addEstateService(service, estate4);
    Estate *estate5 = createEstate("apartment", "12 Oak Street", 75, 900);
    addEstateService(service, estate5);
    Estate *estate6 = createEstate("penthouse", "96 Elm Street", 250, 5000);
    addEstateService(service, estate6);
    Estate *estate7 = createEstate("house", "170 Pine Road", 125, 100);
    addEstateService(service, estate7);
    Estate *estate8 = createEstate("apartment", "29 Spruce Boulevard", 60, 2000);
    addEstateService(service, estate8);
    Estate *estate9 = createEstate("penthouse", "80 Spruce Boulevard", 210, 6000);
    addEstateService(service, estate9);
    Estate *estate2 = createEstate("house", "80 Elm Street", 200, 9999);
    addEstateService(service, estate2);
    if(service->typeOfUndoRedo == 1)
        resetUndoOperations(service->undoRedoRepository);
    else
        resetUndoDynamicArray(service->undoRedoRepository);

}

Service *createService(Repo *REA_repo, UndoRedoRepository *undoRedoRepository, int typeOfUndoRedo){
    Service *service = (Service*)malloc(sizeof(Service));
    service->repo = REA_repo;
    //generateEntries(service);
    service->undoRedoRepository = undoRedoRepository;
    service->typeOfUndoRedo = typeOfUndoRedo;

    return service;
}

Repo *getRepository(Service *service)
{
    return service->repo;
}

UndoRedoRepository *getUndoRedoRepository(Service *service)
{
    return service->undoRedoRepository;
}

int getTypeOfUndoRedo(Service *service)
{
    return service->typeOfUndoRedo;
}


void destroyService(Service *service){
    destroyRepo(getRepository(service));
    destroyUndoRedoRepository(getUndoRedoRepository(service));
    free(service);
}
int addEstateService(Service *service, Estate *estate){
    int exists= check_if_exists(service->repo, estate);
    if(exists==-1){
        if (getTypeOfUndoRedo(service) == 1)
        {
            resetRedoOperations(getUndoRedoRepository(service));
            Operation *operation = createOperation(2, estate, NULL);
            addUndoOperation(getUndoRedoRepository(service), operation);
        }
        else
        {
            resetRedoDynamicArray(getUndoRedoRepository(service));
            DynamicArray *dynamicArray = copyDynamicArrayOfEstates(getDynamicArray(getRepository(service)));
            addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
        }
        addREA(getRepository(service), estate);
        return 1;
    }
    return 0;
}
int deleteEstateService(Service *service, Estate *estate){
    int exists= check_if_exists(service->repo, estate);
    if(exists==-1){
        return 0;
    }
    if (getTypeOfUndoRedo(service) == 1)
    {
        resetRedoOperations(getUndoRedoRepository(service));
        addUndoOperation(getUndoRedoRepository(service), createOperation(1, estate, NULL));
    }
    else
    {
        resetRedoDynamicArray(getUndoRedoRepository(service));
        DynamicArray *dynamicArray = copyDynamicArrayOfEstates(getDynamicArray(getRepository(service)));
        addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
    }
    deleteREA(service->repo, exists);
    return 1;
}

int updateEstateService(Service* service, Estate* estate, Estate* newEstate) {
    int exists= check_if_exists(service->repo, estate);
    destroyEstate(estate);
    if (exists == -1)
    {
        destroyEstate(newEstate);
        return 0;
    }
    if (getTypeOfUndoRedo(service) == 1)
    {
        resetRedoOperations(getUndoRedoRepository(service));
        Estate *estateFromRepository = getEstateFromRepository(getRepository(service), exists);
        Operation *operation = createOperation(3, newEstate, estateFromRepository);
        addUndoOperation(getUndoRedoRepository(service), operation);
    }
    else
    {
        resetRedoDynamicArray(getUndoRedoRepository(service));
        DynamicArray *dynamicArray = copyDynamicArrayOfEstates(getDynamicArray(getRepository(service)));
        addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
    }
    updateREA(service->repo, exists, newEstate);
    //sortEstate(service->repo, &smallerPrice);
    return 1;
}

int undoRedoService(Service *service, DynamicArray *undoFromThisArray, DynamicArray *redoToThisArray)
{
    if (getTypeOfUndoRedo(service) == 1)
    {
        if (getLengthOfDynamicArray(undoFromThisArray) == 0)
            return 0;
        Operation *operation = (Operation *)getElementOnIndex(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
        Operation *operationToBeAddedToRedo = NULL;

        if (getTypeOfOperation(operation) == 1)
        {
            addREA(getRepository(service), copyEstate(getEstate1(operation)));
            operationToBeAddedToRedo = createOperation(2, getEstate1(operation), NULL);
        }
        else if (getTypeOfOperation(operation) == 2)
        {
            deleteREA(getRepository(service), check_if_exists(getRepository(service), getEstate1(operation)));
            operationToBeAddedToRedo = createOperation(1, getEstate1(operation), NULL);
        }
        else if (getTypeOfOperation(operation) == 3)
        {
            updateREA(getRepository(service), check_if_exists(getRepository(service), getEstate1(operation)), copyEstate(getEstate2(operation)));
            operationToBeAddedToRedo = createOperation(3, getEstate2(operation), getEstate1(operation));
        }
        addElementToDA(redoToThisArray, operationToBeAddedToRedo);
        deleteElementFromDA(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
    }
    else if (getTypeOfUndoRedo(service) == 2)
    {
        if (getLengthOfDynamicArray(undoFromThisArray) == 0)
            return 0;
        DynamicArray *dynamicArray = (DynamicArray *)getElementOnIndex(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
        DynamicArray *dynamicArrayToBeAddedToRedo = copyDynamicArrayOfEstates(getDynamicArray(getRepository(service)));
        addElementToDA(redoToThisArray, dynamicArrayToBeAddedToRedo);
        DynamicArray *swap1;
        swap1 = getDynamicArray(getRepository(service));
        service->repo->dynamicArrayAgency = copyDynamicArrayOfEstates(dynamicArray);
        destroyDynamicArray(swap1);
        deleteElementFromDA(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
    }
    return 1;
}

DynamicArray* getEstateBasedOnFiltering(Service* service, char* string, OperationOfComparison operationOfComparison) {
    sortEstate(getRepository(service), &smallerPrice);
    string[strlen(string) - 1] = '\0';
    DynamicArray* dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyEstate);
    for (int i = 0; i < getRepoSize(getRepository(service)); ++i) {
        Estate* estate = getEstateFromRepository(getRepository(service), i);
        if (operationOfComparison(estate, string)) {
            addElementToDA(dynamicArray, copyEstate(estate));
        }
    }
    return dynamicArray;
}

DynamicArray* getEstateBasedOnType(Service* service, char* string, OperationOfComparison operationOfComparison) {
    sortEstate(getRepository(service), (OperationOfComparisonBetweenEstates) operationOfComparison);
    string[strlen(string) - 1] = '\0';
    DynamicArray* dynamicArray = createDynamicArray(10, destroyEstate);
    for (int i = 0; i < getRepoSize(service->repo); ++i) {
        Estate* estate = getEstateFromRepository(service->repo, i);
        if (operationOfComparison(estate, string)) {
            Estate *estateCopy = createEstate(estate->type, estate->address, estate->surface, estate->price);
            addElementToDA(dynamicArray, estateCopy);
        }
    }
    return dynamicArray;
}

DynamicArray* getEstateWithSurface(Service* service, int surface, OperationOfComparisonBetweenEstates operationOfComparisonBetweenEstates) {
    sortEstate(service->repo, operationOfComparisonBetweenEstates);
    DynamicArray* dynamicArray = createDynamicArray(10, destroyEstate);
    for (int i = 0; i < getRepoSize(service->repo); ++i) {
        Estate* estate = getEstateFromRepository(service->repo, i);
        if (estate->surface >= surface) {
            Estate *estateCopy = createEstate(estate->type, estate->address, estate->surface, estate->price);
            addElementToDA(dynamicArray, estateCopy);
        }
    }
    return dynamicArray;
}