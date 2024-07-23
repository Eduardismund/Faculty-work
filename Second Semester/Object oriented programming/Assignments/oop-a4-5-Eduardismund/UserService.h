#include "AdoptedRepo.h"
#include "ShelterRepository.h"

#pragma once

class UserService{
private:
    ShelterRepository &shelterRepository;
    AdoptedRepo &adoptedRepo;
    int currentIndex = 0;
public:
    UserService(ShelterRepository &shelterRepository, AdoptedRepo &adoptedRepo);
    ~UserService();

    DynamicVector<Dog> getDogShelter();
    DynamicVector<Dog> getDogsAdopted();
    DynamicVector<Dog> getDogsFiltered(const std::string &breed, int age);

    Dog getCurrentDog();
    void nextDog();

    void adoptDog(const Dog& dog);
    void adoptDog(const std::string &name);



};