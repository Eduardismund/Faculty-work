
#ifndef A2_3_EDUARDISMUND_SERVICE_H
#define A2_3_EDUARDISMUND_SERVICE_H

#endif //A2_3_EDUARDISMUND_SERVICE_H
#include "../repo/Repo.h"
#include "UndoRedoRepository.h"
#pragma once

typedef struct{
    Repo* repo;
    UndoRedoRepository *undoRedoRepository;
    int typeOfUndoRedo;
}Service;

Service *createService(Repo* , UndoRedoRepository*, int);
void generateEntries(Service *service);
void destroyService(Service* );
int addEstateService(Service* , Estate*);
int deleteEstateService(Service*, Estate*);
int updateEstateService(Service*, Estate *, Estate*);
int undoRedoService(Service *, DynamicArray *, DynamicArray *);
int undoService(Service *);
int redoService(Service *);
int getTypeOfUndoRedo(Service *);
Repo *getRepository(Service *);
UndoRedoRepository *getUndoRedoRepository(Service *);
DynamicArray *getEstateBasedOnFiltering(Service*, char*, OperationOfComparison);
DynamicArray *getEstateBasedOnType(Service*, char*, OperationOfComparison);
DynamicArray *getEstateWithSurface(Service*, int, OperationOfComparisonBetweenEstates);

