#pragma once
#include <string>
#include "Dog.h"
#include <vector>
#include "RepoAdoptedDogs.h"
#include "RepoShelterDogs.h"


class ServiceUser{
private:
    RepoShelterDogs *shelterRepository;
    RepoAdoptedDogs *adoptedRepo;
    std::string shelterFile;
    std::string adoptedFile;
    int currentIndex = 0;
public:
    ServiceUser(RepoShelterDogs *shelterRepository, RepoAdoptedDogs *adoptedRepo, std::string shelterFile_ = "ShelterDogs.txt", std::string adoptedFile_ = "AdoptedDogs.txt");
    ~ServiceUser();

    std::vector<Dog> getDogShelter();
    std::vector<Dog> getDogsAdopted();
    std::vector<Dog> getDogsFiltered(const std::string &breed, int age);

    Dog getCurrentDog();
    void nextDog();

    void adoptDog(const Dog& dog);
    void adoptDog(const std::string &name);


    // read and save shelter dogs from/to file
    void readShelterDogFromFile();
    void saveShelterDogToFile();

    // read and save adopted dogs from/to file
    void readAdoptedDogFromFile();
    void saveAdoptedDogToFile();

    RepoAdoptedDogs *const getRepoAdopted() const {
        return adoptedRepo;
    }


};