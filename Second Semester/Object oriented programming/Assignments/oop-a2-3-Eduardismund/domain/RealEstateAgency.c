#include "RealEstateAgency.h"
#include "Operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Estate *createEstate(char *type, char *address, int surface, int price){
    Estate *estate = (Estate *)malloc(sizeof(Estate));
    estate->type = (char *)malloc(sizeof(char) * (strlen(type)+1));
    strcpy(estate->type, type);
    estate->address= (char *)malloc(sizeof(char) * (strlen(address)+1));
    strcpy(estate->address, address);
    estate->price=price;
    estate->surface=surface;
    return estate;
}
char *getAddress(Estate *estate)
{
    return estate->address;
}
Estate *copyEstate(Estate *estate)
{
    return createEstate(estate->type, estate->address, estate->surface, estate->price);
}
int EstateContainsString(Estate* estate, char *string) {
    return ((strstr(estate->address, string) != NULL) );
}

int EstateTypeContainsString(Estate* estate, char *string) {
    if(strcmp(estate->type, string) == 0)
        return 1;
    return 0;
}

void destroyEstate(Estate *estate){
//    free(estate->type);
//    free(getAddress(estate));
//    free(estate);
    if(estate){
        if(estate->type)
            free(estate->type);
        if(estate->address)
            free(estate->address);
        free(estate);
    }

}

char *formattedEstate(Estate *estate){
    char *string = (char *)malloc(sizeof(char)*500);
    sprintf(string, "Type: %s | Address: %s | Surface: %d | Price: %d", estate->type, estate->address, estate->surface, estate->price);
    return string;
}

int compareEstates(Estate *estate1, Estate *estate2){
    if(strcmp(estate1->address, estate2->address)==0)
        return 1;
    return 0;
}

int smallerPrice(Estate *estate1, Estate *estate2) {
    return (estate1->price < estate2->price);
}

int smallerSurface(Estate *estate1, Estate *estate2) {
    return (estate1->surface < estate2->surface);
}

int greaterSurface(Estate *estate1, Estate *estate2) {
    return (estate1->surface> estate2->surface);
}