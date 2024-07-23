# include "Dog.h"
#include "Exception.h"
#include <iostream>

using namespace std;

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

ostream &operator<<(ostream &os, const Dog &dog){
    if(&os == &cout)
        os << "Name: ";
    os<<dog.name<<"\n";
    if(&os == &cout)
        os << "Breed: ";
    os<<dog.breed<<"\n";
    if(&os == &cout)
        os << "Age: ";
    os<<dog.age<<"\n";
    if(&os == &cout)
        os << "Photograph: ";
    os<<dog.photograph<<"\n";
    return os;
}

istream &operator>>(istream &is, Dog& dog) {

    string name, breed, stringAge, photograph;

    if (&is == &cin) {
        cout << "Name: ";
        getchar();
    }
    getline(is, name);
    if (name == "\n" || name.empty())
        throw Exception(" ");

    if (&is == &cin)
        cout << "Breed: ";
    getline(is, breed);

    if (&is == &cin)
        cout << "Age: ";
    getline(is, stringAge);
    if(stringAge.find('\r') != string::npos)
        stringAge.erase(stringAge.find('\r'), 1);

    if (&is == &cin)
        while (!DogValidator::validateAge(stringAge)) {
            cout << "Invalid age! Please enter a valid age: ";
            is >> stringAge;
        }
    else if (!DogValidator::validateAge(stringAge))
        throw Exception("There is something wrong with the age!(in the file probabily)");

    int age = stoi(stringAge);
    if (&is == &cin)
        cout << "Photograph: ";
    getline(is, photograph);

    dog.setName(name);
    dog.setBreed(breed);
    dog.setAge(age);
    dog.setPhotograph(photograph);

    return is;
}
bool DogValidator::validateAge(const string& stringAge) {
    if (stringAge.find_first_not_of("0123456789") != string::npos) {
        return false;
    } else if (stoi(stringAge) < 0 || stoi(stringAge) > 20) {
        return false;
    }
    return true;
}