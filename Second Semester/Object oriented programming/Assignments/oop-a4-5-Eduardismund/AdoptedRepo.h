#pragma once
#include "Dog.h"
#include "DynamicArray.h"


class AdoptedRepo{
private:
    DynamicVector<Dog> vectorWithAdoptedDogs;
public:
    AdoptedRepo();
    ~AdoptedRepo();

    void addAdoption(const Dog &dog);
    DynamicVector<Dog> getAdoption();

};