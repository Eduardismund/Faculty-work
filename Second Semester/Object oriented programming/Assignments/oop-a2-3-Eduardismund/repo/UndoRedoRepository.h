//
// Created by User on 3/14/2024.
//
#include "DynamicArray.h"
#include "Repo.h"
#include "Operation.h"

#ifndef A2_3_EDUARDISMUND_UNDOREDOREPOSITORY_H
#define A2_3_EDUARDISMUND_UNDOREDOREPOSITORY_H
#pragma once
#endif //A2_3_EDUARDISMUND_UNDOREDOREPOSITORY_H
typedef struct
{
    DynamicArray *undoOperations;
    DynamicArray *redoOperations;
} UndoRedoRepository;

UndoRedoRepository *createUndoRedoRepository(int);
DynamicArray *getUndoOperations(UndoRedoRepository *);
DynamicArray *getRedoOperations(UndoRedoRepository *);
void destroyUndoOperations(UndoRedoRepository *);
void destroyRedoOperations(UndoRedoRepository *);
void resetRedoOperations(UndoRedoRepository *);
void resetRedoDynamicArray(UndoRedoRepository *);
void destroyUndoRedoRepository(UndoRedoRepository *);
void addUndoOperation(UndoRedoRepository *, Operation *);
void addUndoDynamicArray(UndoRedoRepository *, DynamicArray *);
void setTypeOfUndoRedo(UndoRedoRepository *undoRedoRepository, int typeOfUndoRedo);
void resetUndoOperations(UndoRedoRepository *undoRedoRepository);
void resetUndoDynamicArray(UndoRedoRepository *undoRedoRepository);

