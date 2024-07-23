#include "ServiceUser.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include "Exception.h"
using namespace std;


ServiceUser::ServiceUser(RepoShelterDogs *shelterRepository, RepoAdoptedDogs *adoptedRepo, std::string shelterFile_, std::string adoptedFile_): shelterRepository(shelterRepository), shelterFile{std::move(shelterFile_)}, adoptedFile{std::move(adoptedFile_)} {
    this->adoptedRepo = adoptedRepo;
}

ServiceUser::~ServiceUser() =default;

std::vector<Dog> ServiceUser::getDogShelter() {
    return this->shelterRepository->getDogs();
}

std::vector<Dog> ServiceUser::getDogsAdopted() {
    return this->adoptedRepo->getAdoption();
}

std::vector<Dog> ServiceUser::getDogsFiltered(const std::string &breed, int age) {
    std::vector<Dog> allDogs = this->shelterRepository->getDogs();
    std::vector<Dog> filteredDogs;

    auto filterFunction = [&](const Dog& currentDog) {
        return (currentDog.getBreed() == breed || breed.empty()) && currentDog.getAge() < age;
    };

    std::copy_if(allDogs.begin(), allDogs.end(), std::back_inserter(filteredDogs), filterFunction);

    return filteredDogs;
}

Dog ServiceUser::getCurrentDog() {
    return this->getDogShelter()[this->currentIndex];
}

void ServiceUser::nextDog() {
    this->currentIndex = (this->currentIndex+1) % this->getDogShelter().size();
}

//adopt a dog
void ServiceUser::adoptDog(const std::string &name) {
    Dog dog = this->shelterRepository->getDogByName(name);
    this->adoptDog(dog);

    this->saveShelterDogToFile();
    this->saveAdoptedDogToFile();
}

void ServiceUser::adoptDog(const Dog &dog) {
    this->shelterRepository->deleteDog(dog.getName());
    this->adoptedRepo->addAdoption(dog);

    // save changes to file
    this->saveShelterDogToFile();
    this->saveAdoptedDogToFile();
}

void ServiceUser::readShelterDogFromFile() {
    ifstream file(shelterFile);
    Dog dog{};
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    while (file.good()) {
        file >> dog;
        this->shelterRepository->addDog(dog);
    }
    file.close();
}

void ServiceUser::saveShelterDogToFile() {
    ofstream file(shelterFile);
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    for (const auto &dog: this->shelterRepository->getDogs()) {
        file << dog;
    }
    file.close();
}

void ServiceUser::readAdoptedDogFromFile() {
    ifstream file(adoptedFile);
    Dog dog{};
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    while (file.good()) {
        try{
            file >> dog;
            this->adoptedRepo->addAdoption(dog);
        }catch (exception& e) {
            cout << e.what() << endl;

        }
    }
    file.close();
}

void ServiceUser::saveAdoptedDogToFile() {
    ofstream file(adoptedFile);
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    for (const auto &dog: this->adoptedRepo->getAdoption()) {
        file << dog;
    }
    file.close();
}

