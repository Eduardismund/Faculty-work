#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "testEstate.h"
#include "RealEstateAgency.h"

void testEstateCreateAndDelete()
{
    Estate *Estate = createEstate("house", "15 Spruce Boulevard", 150, 1500);
    assert(Estate != NULL);
    assert(strcmp(Estate->type, "house") == 0);
    assert(strcmp(Estate->address, "15 Spruce Boulevard") == 0);
    assert(Estate->surface == 150);
    assert(Estate->price == 1500);
    destroyEstate(Estate);
}

void testEstateCopy()
{
    Estate *copy;
    Estate *Estate = createEstate("apartment", "12 Oak Street", 75, 900);
    copy = copyEstate(Estate);
    assert(copy != NULL);
    assert(strcmp(copy->type, "apartment") == 0);
    assert(strcmp(copy->address, "12 Oak Street") == 0);
    assert(Estate->surface == 75);
    assert(Estate->price == 900);
    destroyEstate(Estate);
    destroyEstate(copy);
}

void testEstateFormat()
{
    Estate *Estate = createEstate("penthouse", "96 Elm Street", 250, 5000);
    char *formattedEstateString = formattedEstate(Estate);
    assert(formattedEstateString != NULL);
    assert(strcmp(formattedEstateString, "Type: penthouse | Address: 96 Elm Street | Surface: 250 | Price: 5000") == 0);
    destroyEstate(Estate);
    free(formattedEstateString);
}

void testEstateComparisons()
{
    Estate *Estate1 = createEstate("apartment", "12 Oak Street", 75, 900);
    Estate *Estate2 = createEstate("penthouse", "96 Elm Street", 250, 5000);
    Estate *Estate3 = createEstate("house", "12 Oak Street", 150, 1500);
    assert(compareEstates(Estate1, Estate2) == 0);
    assert(compareEstates(Estate2, Estate1) == 0);
    assert(compareEstates(Estate1, Estate3));
    assert(compareEstates(Estate3, Estate1));
    assert(EstateContainsString(Estate1, "12 Oak Street") == 1);
    assert(EstateContainsString(Estate1, "12 Oaaaak Street") == 0);
    assert(smallerPrice(Estate1, Estate2) == 1);
    assert(smallerPrice(Estate2, Estate1) == 0);
    assert(smallerSurface(Estate1, Estate2) == 1);
    assert(smallerSurface(Estate2, Estate1) == 0);
    assert(greaterSurface(Estate1, Estate2) == 0);
    assert(greaterSurface(Estate2, Estate1) == 1);
    destroyEstate(Estate1);
    destroyEstate(Estate2);
    destroyEstate(Estate3);
}

void testEstateAll()
{
    testEstateCreateAndDelete();
    testEstateCopy();
    testEstateFormat();
    testEstateComparisons();
}