#include "ShelterRepository.h"

ShelterRepository::ShelterRepository() {
    this->dogs = DynamicVector<Dog>();
}

ShelterRepository::~ShelterRepository() = default;

//add
void ShelterRepository::addDog(const std::string &name, const std::string &breed, const std::string &photograph,
                               int age) {
    Dog dogToAdd = Dog(breed, name, photograph, age);
    this->dogs.addElement(dogToAdd);
}

//update
void ShelterRepository::updateDog(const std::string &name, const std::string &newBreed,
                                  const std::string &newPhotograph, int newAge) {
    Dog updatedDog = Dog(newBreed, name, newPhotograph, newAge);
    int position = getDogPositionByName(name);
    this->dogs.setElement(position, updatedDog);
}

//remove
void ShelterRepository::deleteDog(const std::string &name) {
    int position = this->getDogPositionByName(name);
    this->dogs.removeElementFromPosition(position);
}

//get them dogs
DynamicVector<Dog> ShelterRepository::getDogs() const {
    return this->dogs;
}

int ShelterRepository::getDogPosition(const Dog &dog) {
    for(int i = 0; i<this->dogs.getSize(); i++)
        if(this->dogs[i]== dog)
            return i;
    return -1;
}

//get dog position by name
int ShelterRepository::getDogPositionByName(const std::string &name) {
    for(int i = 0; i<this->dogs.getSize(); i++)
        if(this->dogs[i].getName()==name)
            return i;
    return -1;
}

//get dog by name
Dog ShelterRepository::getDogByName(const std::string &name) {
    for(int i = 0; i<this->dogs.getSize(); i++)
        if(this->dogs[i].getName()==name)
            return this->dogs[i];
    return {};
}