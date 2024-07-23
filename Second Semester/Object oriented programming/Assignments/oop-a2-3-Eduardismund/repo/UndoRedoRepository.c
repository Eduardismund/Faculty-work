#include "UndoRedoRepository.h"
#include "Repo.h"
#include <stdlib.h>
#include <string.h>

UndoRedoRepository *createUndoRedoRepository(int typeOfUndoRedo)
{
    UndoRedoRepository *undoRedoRepository = (UndoRedoRepository *)malloc(sizeof(UndoRedoRepository));
    if (typeOfUndoRedo == 1)
    {
        undoRedoRepository->undoOperations = createDynamicArray(1000, destroyOperation);
        undoRedoRepository->redoOperations = createDynamicArray(1000, destroyOperation);
    }
    else
    {
        undoRedoRepository->undoOperations = createDynamicArray(1000, destroyDynamicArray);
        undoRedoRepository->redoOperations = createDynamicArray(1000, destroyDynamicArray);
    }
    return undoRedoRepository;
}

void destroyUndoOperations(UndoRedoRepository *undoRedoRepository)
{
    destroyDynamicArray(getUndoOperations(undoRedoRepository));
}

void destroyRedoOperations(UndoRedoRepository *undoRedoRepository)
{
    destroyDynamicArray(getRedoOperations(undoRedoRepository));
}

DynamicArray *getUndoOperations(UndoRedoRepository *undoRedoRepository)
{
    return undoRedoRepository->undoOperations;
}

DynamicArray *getRedoOperations(UndoRedoRepository *undoRedoRepository)
{
    return undoRedoRepository->redoOperations;
}

void resetRedoOperations(UndoRedoRepository *undoRedoRepository)
{
    destroyRedoOperations(undoRedoRepository);
    undoRedoRepository->redoOperations = createDynamicArray(1000, destroyOperation);
}
void resetUndoOperations(UndoRedoRepository *undoRedoRepository)
{
    destroyUndoOperations(undoRedoRepository);
    undoRedoRepository->undoOperations = createDynamicArray(1000, destroyOperation);
}

void resetRedoDynamicArray(UndoRedoRepository *undoRedoRepository)
{
    destroyRedoOperations(undoRedoRepository);
    undoRedoRepository->redoOperations = createDynamicArray(1000, destroyDynamicArray);
}

void resetUndoDynamicArray(UndoRedoRepository *undoRedoRepository)
{
    destroyUndoOperations(undoRedoRepository);
    undoRedoRepository->undoOperations = createDynamicArray(1000, destroyDynamicArray);
}
void destroyUndoRedoRepository(UndoRedoRepository *undoRedoRepository)
{
    destroyUndoOperations(undoRedoRepository);
    destroyRedoOperations(undoRedoRepository);
    free(undoRedoRepository);
}

void addUndoOperation(UndoRedoRepository *undoRedoRepository, Operation *operation)
{
    addElementToDA(getUndoOperations(undoRedoRepository), operation);
}


void addUndoDynamicArray(UndoRedoRepository *undoRedoRepository, DynamicArray *dynamicArray)
{
    addElementToDA(getUndoOperations(undoRedoRepository), dynamicArray);
}

void setTypeOfUndoRedo(UndoRedoRepository *undoRedoRepository, int typeOfUndoRedo)
{
    if (typeOfUndoRedo == 1)
    {
        destroyUndoOperations(undoRedoRepository);
        destroyRedoOperations(undoRedoRepository);
        undoRedoRepository->undoOperations = createDynamicArray(1000, destroyOperation);
        undoRedoRepository->redoOperations = createDynamicArray(1000, destroyOperation);
    }
    else
    {
        destroyUndoOperations(undoRedoRepository);
        destroyRedoOperations(undoRedoRepository);
        undoRedoRepository->undoOperations = createDynamicArray(1000, destroyDynamicArray);
        undoRedoRepository->redoOperations = createDynamicArray(1000, destroyDynamicArray);
    }
}