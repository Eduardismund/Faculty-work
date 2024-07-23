#include "AdoptedRepo.h"

AdoptedRepo::AdoptedRepo() {
    this->vectorWithAdoptedDogs = DynamicVector<Dog>();
}

AdoptedRepo::~AdoptedRepo()=default;

DynamicVector<Dog> AdoptedRepo::getAdoption() {
    return this->vectorWithAdoptedDogs;
}

void AdoptedRepo::addAdoption(const Dog &dog) {
    this->vectorWithAdoptedDogs.addElement(dog);
}