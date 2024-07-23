#include "AdminService.h"
#include "Exception.h"

AdminService::AdminService(ShelterRepository &adminRepoDogs): adminRepo(adminRepoDogs){

}

AdminService::~AdminService() = default;

void AdminService::addDog(const std::string &breed, const std::string &name, const std::string &photograph, int age) {
    if(this->getDogPositionByName(name) != -1)
        throw Exception("A dog with the same name already exists. try another one!");
    this->adminRepo.addDog(name, breed, photograph, age);
}

void AdminService::deleteDog(const std::string &name) {
    if(this->getDogPositionByName(name) == -1)
        throw Exception("A dog with that name does not exist. try another one!");
    this->adminRepo.deleteDog(name);
}

void AdminService::updateDog(const std::string &name, const std::string &newBreed, const std::string &newPhotograph,
                             int newAge) {
    if(this->getDogPositionByName(name) == -1)
        throw Exception("A dog with that name does not exist. try another one!");
    this->adminRepo.updateDog(name, newBreed, newPhotograph, newAge);
}

DynamicVector<Dog> AdminService::getDogs() const {
    return this->adminRepo.getDogs();
}

int AdminService::getDogPositionByName(const std::string &name) {
    return this->adminRepo.getDogPositionByName(name);
}

int AdminService::getDogPosition(const Dog &dog) {
    return this->adminRepo.getDogPosition(dog);
}

Dog AdminService::getDogByName(const std::string &name) {
    int position = this->getDogPositionByName(name);
    if(position == -1)
        throw Exception("The dog does not exist!");
    else
        return this->adminRepo.getDogs()[position];
}