#include "UserService.h"

UserService::UserService(ShelterRepository &shelterRepository,  AdoptedRepo &adoptedRepo):shelterRepository(shelterRepository), adoptedRepo(adoptedRepo)
{}

UserService::~UserService() =default;

DynamicVector<Dog> UserService::getDogShelter() {
    return this->shelterRepository.getDogs();
}

DynamicVector<Dog> UserService::getDogsAdopted() {
    return this->adoptedRepo.getAdoption();
}

DynamicVector<Dog> UserService::getDogsFiltered(const std::string &breed, int age) {
    DynamicVector<Dog> allDogs = this->shelterRepository.getDogs();
    DynamicVector<Dog> filteredDogs;
    for(int i = 0; i< allDogs.getSize(); i++) {
        Dog currentDog = allDogs[i];
        if ((currentDog.getBreed() == breed or breed.empty()) && currentDog.getAge() < age)
            filteredDogs.addElement(currentDog);
    }
    return filteredDogs;
}

Dog UserService::getCurrentDog() {
    return this->getDogShelter()[this->currentIndex];
}

void UserService::nextDog() {
    this->currentIndex = (this->currentIndex+1) % this->getDogShelter().getSize();
}

//adopt a dog
void UserService::adoptDog(const std::string &name) {
    Dog dog = this->shelterRepository.getDogByName(name);
    this->adoptDog(dog);
}

void UserService::adoptDog(const Dog &dog) {
    this->shelterRepository.deleteDog(dog.getName());
    this->adoptedRepo.addAdoption(dog);
}


