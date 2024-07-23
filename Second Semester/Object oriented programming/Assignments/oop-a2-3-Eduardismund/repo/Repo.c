#include "Repo.h"
#include <stdlib.h>
#pragma once


Repo* createRepository(){
    Repo *REA_repo = (Repo *)malloc(sizeof(Repo));
    if (REA_repo == NULL)
        return NULL;
    REA_repo->dynamicArrayAgency= createDynamicArray(100, destroyEstate);
    return REA_repo;
}
DynamicArray *getDynamicArray(Repo *repository)
{
    return repository->dynamicArrayAgency;
}
int getRepoSize(Repo *REA_repo){
    return REA_repo->dynamicArrayAgency->size;
}

void destroyRepo(Repo *REA_repo){
    destroyDynamicArray(getDynamicArray(REA_repo));
    free(REA_repo);
}

void addREA(Repo *REA_repo, Estate *estate){
    addElementToDA(REA_repo->dynamicArrayAgency, estate);
}

void deleteREA(Repo *REA_repo, int index){
    deleteElementFromDA(REA_repo->dynamicArrayAgency, index);
}

void updateREA(Repo *REA_repo, int index, Estate *estate){
    updateElementAnIndex(REA_repo->dynamicArrayAgency, index, estate);
}
int check_if_exists(Repo *REA_repo, Estate *estate){
    for(int j=0;j<getRepoSize(REA_repo);++j)
        if(compareEstates((Estate*)(getElementOnIndex(REA_repo->dynamicArrayAgency, j)), estate)==1)
            return j;
    return -1;
}

void sortEstate(Repo* repository, OperationOfComparisonBetweenEstates operationOfComparisonBetweenEstates) {
    for (int i = 0; i < repository->dynamicArrayAgency->size - 1; ++i) {
        for (int j = i + 1; j < repository->dynamicArrayAgency->size; ++j) {
            Estate *estate1 = (Estate*)getElementOnIndex(repository->dynamicArrayAgency, i);
            Estate *estate2 = (Estate*)getElementOnIndex(repository->dynamicArrayAgency, j);
            if (operationOfComparisonBetweenEstates(estate2, estate1) > 0)
                swapElementsOnDynamicArray(repository->dynamicArrayAgency, i, j);
        }
    }
}

Estate *getEstateFromRepository(Repo *repository, int position) {
    return (Estate*)(getElementOnIndex(repository->dynamicArrayAgency, position));
}


int getRepositoryLength(Repo *repository)
{
    return getLengthOfDynamicArray(getDynamicArray(repository));
}
void deleteEstateFromRepository(Repo *repository, int position)
{
    deleteElementFromDA(getDynamicArray(repository), position);
}

Repo *copyRepository(Repo *repository)
{
    Repo *newRepository = createRepository();
    int length = getRepositoryLength(repository);
    for (int i = 0; i < length; ++i)
    {
        Estate *estate = getEstateFromRepository(repository, i);
        addElementToDA(newRepository, copyEstate(estate));
    }
    newRepository->dynamicArrayAgency->size = length;
    return newRepository;
}

void setRepository(Repo *repository, Repo *newRepository)
{
    destroyRepo(repository);
    repository = copyRepository(newRepository);
}