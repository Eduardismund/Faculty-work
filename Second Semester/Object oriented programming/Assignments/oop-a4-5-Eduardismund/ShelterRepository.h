#pragma once
#include "DynamicArray.h"
#include "Dog.h"

class ShelterRepository{
private:
    DynamicVector<Dog> dogs;
public:
    ShelterRepository();
    ~ShelterRepository();
    void addDog(const std::string &name, const std::string &breed, const std::string &photograph, int age);
    void updateDog(const std::string &name, const std::string &newBreed, const std::string &newPhotograph, int newAge);
    void deleteDog(const std::string &name);
    DynamicVector<Dog> getDogs() const;
    int getDogPosition(const Dog& dog);
    int getDogPositionByName(const std::string &name);
    Dog getDogByName(const std::string &name);
};