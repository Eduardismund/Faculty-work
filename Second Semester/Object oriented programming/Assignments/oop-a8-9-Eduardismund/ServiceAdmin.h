#pragma once
#include "RepoShelterDogs.h"
#include "Dog.h"

class AdminService{
private:
    RepoShelterDogs* adminRepo;
    std::string shelterFile;
public:
    explicit AdminService(RepoShelterDogs* adminRepoDogs, std::string shelterFile_ = "ShelterDogs.txt");
    ~AdminService();
    void addDog(const Dog &dog);
    void addDog(const std::string &breed, const std::string &name, const std::string &photograph, int age);
    void updateDog(const std::string &name, const std::string &newBreed, const std::string &newPhotograph, int newAge);
    void deleteDog(const std::string &name);
    std::vector<Dog> getDogs() const;
    int getDogPosition(const Dog& dog);
    int getDogPositionByName(const std::string &name);
    Dog getDogByName(const std::string &name);
    void setRepository(RepoShelterDogs *repoToBeSet){
        AdminService::adminRepo=repoToBeSet;
    }
};

class ServiceValidator {
public:
    static bool validateDogExists(const std::vector<Dog>& dogs, const std::string& name);
};