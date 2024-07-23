//
// Created by User on 3/5/2024.
//

#ifndef A2_3_EDUARDISMUND_REPO_H
#define A2_3_EDUARDISMUND_REPO_H
#pragma once

#endif //A2_3_EDUARDISMUND_REPO_H
#include "../dynamicArray/DynamicArray.h"
#include "../domain/RealEstateAgency.h"

typedef struct{
    DynamicArray *dynamicArrayAgency;
}Repo;

Repo* createRepository();
int getRepoSize(Repo *);
int check_if_exists(Repo *, Estate *);
void destroyRepo(Repo *);
void addREA(Repo *, Estate *);
void deleteREA(Repo *, int);
void updateREA(Repo *, int, Estate *);
Estate* getEstateFromRepository(Repo* , int);
void sortEstate(Repo*, OperationOfComparisonBetweenEstates);
DynamicArray *getDynamicArray(Repo *);
Repo *copyRepository(Repo *);
