#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "testService.h"
#include "RealEstateAgency.h"
#include "Service.h"

void testStartService(int typeOfUndoRedo)
{
    Repo *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
    assert(getRepository(service) == repository);
    assert(getUndoRedoRepository(service) == undoRedoRepository);
    assert(getTypeOfUndoRedo(service) == typeOfUndoRedo);
    generateEntries(service);
    assert(getRepoSize(getRepository(service)) == 10);
    destroyService(service);
}

void testPerformOperationsOnEstateService(int typeOfUndoRedo)
{
    Estate *estate = createEstate("penthouse", "80 Spruce Boulevard", 210, 6000);
    Repo *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
    Estate *estate1 = createEstate("house", "15 Spruce Boulevard", 150, 1500);
     //Test to see if a new element is added
    assert(addEstateService(service, estate1) == 1);
    Estate *estate2 = createEstate("apartment", "15 Spruce Boulevard", 75, 900);
    // Element with that address already exists, so it shouldn't be added
    assert(addEstateService(service, estate2) == 0);
    // Check the length to see that it was indeed not added
    assert(getRepoSize(getRepository(service)) == 1);
    // Assertion to see if the quantity was updated
    Estate *Estate = createEstate("penthouse", "96 Elm Street", 250, 5000);
    assert(updateEstateService(service, copyEstate(estate2), copyEstate(Estate)) == 1);
    // Test to see if a non existing estate is not deleted
    assert(deleteEstateService(service, estate) == 0);
    // Test to ensure that non existing Estates are not updated
    assert(updateEstateService(service, estate, copyEstate(estate1)) == 0);
    // Test to see if an existing Estate
    assert(deleteEstateService(service, Estate) == 1);
    // Add multiple Estates
    destroyEstate(Estate);
    destroyEstate(estate2);
    //destroyEstate(estate1);
    estate2 = createEstate("penthouse", "96 Elm Street", 250, 5000);
    assert(addEstateService(service, estate2) == 1);
    estate1 = createEstate("apartment", "15 Spruce Boulevard", 75, 900);
    assert(addEstateService(service, estate1) == 1);
    Estate = createEstate("penthouse", "80 Spruce Boulevard", 210, 6000);
    assert(addEstateService(service, Estate) == 1);

    assert(getRepoSize(getRepository(service)) == 3);

    // Test to see if all the entities have been stored in undo
    int lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));
    assert(lengthOfUndoArray == 6 && lengthOfRedoArray == 0);
    for (int i = 0; i < lengthOfUndoArray; ++i)
        assert(undoRedoService(service, getUndoOperations(getUndoRedoRepository(service)), getRedoOperations(getUndoRedoRepository(service))) == 1);

    lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));

    assert(lengthOfUndoArray == 0 && lengthOfRedoArray == 6);
    for (int i = 0; i < lengthOfRedoArray; ++i)
        assert(undoRedoService(service, getRedoOperations(getUndoRedoRepository(service)), getUndoOperations(getUndoRedoRepository(service))) == 1);

    assert(getRepoSize(getRepository(service)) == 3);

    // Test to see the filtering of Estates
    OperationOfComparison operation = &EstateContainsString;
    char stringToSearchFor[101] = "";
    DynamicArray *EstatesFiltered = getEstateBasedOnFiltering(service, stringToSearchFor, operation);
    assert(getLengthOfDynamicArray(EstatesFiltered) == 3);
    destroyDynamicArray(EstatesFiltered);
    char stringToSearchFor1[101] = "Spruce";
    EstatesFiltered = getEstateBasedOnFiltering(service, stringToSearchFor1, operation);
    assert(getLengthOfDynamicArray(EstatesFiltered) == 2);
    destroyDynamicArray(EstatesFiltered);

    // Test to see filtering on surface
    OperationOfComparisonBetweenEstates operationComparisonEstates = &smallerSurface;
    DynamicArray *EstatesQuantityFilter = getEstateWithSurface(service, 220, operationComparisonEstates);
    assert(getLengthOfDynamicArray(EstatesQuantityFilter) == 1);
    estate2 = createEstate("penthouse", "96 Elm Street", 250, 5000);
    estate1 = createEstate("apartment", "15 Spruce Boulevard", 75, 900);
    Estate =(getElementOnIndex(EstatesQuantityFilter, 0));
    assert(compareEstates(Estate, estate2));
    destroyDynamicArray(EstatesQuantityFilter);

}

void testAllService()
{
    testStartService(1);
    testStartService(2);
    testPerformOperationsOnEstateService(1);
    testPerformOperationsOnEstateService(2);
}