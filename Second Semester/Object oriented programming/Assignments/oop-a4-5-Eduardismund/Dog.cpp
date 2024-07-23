# include "Dog.h"
Dog::Dog() {
    this->breed = "";
    this->name = "";
    this->photograph = "";
    this->age = 0;
}
//constructor

Dog::Dog(const std::string &breed, const std::string &name, const std::string &photograph, int age){
    this->breed = breed;
    this->name = name;
    this->photograph = photograph;
    this->age = age;
}

Dog::Dog(const Dog& otherDog) = default;

Dog::~Dog()= default;

Dog& Dog::operator=(const Dog& otherDog) = default;

//GETTERS

std::string Dog::getBreed() const{
    return this->breed;
}

std::string Dog::getName() const{
    return this->name;
}

std::string Dog::getPhotograph() const{
    return this->photograph;
};

int Dog::getAge() const{
    return this->age;
}

//SETTERS

void Dog::setBreed(const std::string &newBreed){
    this->breed = newBreed;
}
void Dog::setName(const std::string &newName){
    this->name = newName;
}
void Dog::setPhotograph(const std::string &newPhotograph){
    this->photograph = newPhotograph;
}
void Dog::setAge(int newAge){
    this->age = newAge;
}

//operator ==

bool Dog::operator==(const Dog& otherDog) const{
    return this->breed == otherDog.breed && this->name == otherDog.name && this->age == otherDog.age && this->photograph == otherDog.photograph;
}


