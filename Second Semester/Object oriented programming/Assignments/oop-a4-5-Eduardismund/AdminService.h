#pragma once
#include "ShelterRepository.h"
#include "Dog.h"

class AdminService{
private:
    ShelterRepository& adminRepo;
public:
    explicit AdminService(ShelterRepository& adminRepoDogs);
    ~AdminService();
    void addDog(const std::string &breed, const std::string &name, const std::string &photograph, int age);
    void updateDog(const std::string &name, const std::string &newBreed, const std::string &newPhotograph, int newAge);
    void deleteDog(const std::string &name);
    DynamicVector<Dog> getDogs() const;
    int getDogPosition(const Dog& dog);
    int getDogPositionByName(const std::string &name);
    Dog getDogByName(const std::string &name);
};