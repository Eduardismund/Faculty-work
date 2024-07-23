//
// Created by User on 3/5/2024.
//

#ifndef A2_3_EDUARDISMUND_REALESTATEAGENCY_H
#define A2_3_EDUARDISMUND_REALESTATEAGENCY_H


#pragma once
typedef struct{
    char *type;
    char *address;
    int surface;
    int price;
} Estate;

typedef int (*OperationOfComparison)(Estate*, char*);
typedef int (*OperationOfComparisonBetweenEstates)(Estate*, Estate*);

Estate *createEstate(char *, char *, int , int);
Estate *copyEstate(Estate *);
void destroyEstate(Estate *);
int EstateContainsString(Estate* , char *);
char *formattedEstate(Estate *);
int smallerPrice(Estate *, Estate *);
int smallerSurface(Estate *, Estate *);
int greaterSurface(Estate *, Estate *);
int compareEstates(Estate *, Estate *);
int EstateTypeContainsString(Estate* , char *);
#endif //A2_3_EDUARDISMUND_REALESTATEAGENCY_H