#include "RepoShelterDogs.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Exception.h"
using namespace std;

FileRepoShelterDogs::FileRepoShelterDogs()  {
    this->readFromFile();
}

//RepoShelterDogs::~RepoShelterDogs() = default;

//void RepoShelterDogs::addDog(const Dog &dog) {
//    this->dogs.push_back(dogToAdd);
//
//}
//add
//void RepoShelterDogs::addDog(const std::string &name, const std::string &breed, const std::string &photograph,
//                             int age) {
//    Dog dogToAdd = Dog(breed, name, photograph, age);
//    this->dogs.push_back(dogToAdd);
//}

//update
void FileRepoShelterDogs::updateDog(const Dog &dog) {
    std::string name=dog.getName();
    int position = getDogPositionByName(name);
    this->dogs[position] = dog;
}

//remove
//void RepoShelterDogs::deleteDog(const std::string &name) {
//    int position = this->getDogPositionByName(name);
//    this->dogs.erase(this->dogs.begin()+position);
//}
//
////get them dogs
std::vector<Dog> FileRepoShelterDogs::getDogs() const {
    return this->dogs;
}

int FileRepoShelterDogs::getDogPosition(const Dog &dog) {
    auto it = std::find(dogs.begin(), dogs.end(), dog);
    if (it != dogs.end()) {
        return std::distance(dogs.begin(), it);
    }
    return -1;
}

int FileRepoShelterDogs::getDogPositionByName(const std::string &name) {
    auto it = std::find_if(dogs.begin(), dogs.end(), [&](const Dog& d){ return d.getName() == name; });
    if (it != dogs.end()) {
        return std::distance(dogs.begin(), it);
    }
    return -1;
}

Dog FileRepoShelterDogs::getDogByName(const std::string &name) {
    auto it = std::find_if(dogs.begin(), dogs.end(), [&](const Dog& d){ return d.getName() == name; });
    if (it != dogs.end()) {
        return *it;
    }
    return {};
}


void FileRepoShelterDogs::readFromFile() {
    ifstream file1("ShelterDogs.txt");
    Dog dog{};
    if (!file1.is_open()) {
        throw Exception("The file could not be opened!");
    }
    while (file1.good()) {
        try{
            file1 >> dog;
            this->addDog(dog);
        }catch (exception& e) {
            cout << e.what() << endl;

        }
    }
    file1.close();
}

void FileRepoShelterDogs::writeToFile() const {
    std::ofstream file("ShelterDogs.txt");
    if(!file.is_open())
        throw Exception("The file couldn't be opened!");
    for(const auto &dog: this->getDogs())
        file << dog;
    file.close();
}

void FileRepoShelterDogs::addDog(const Dog &dog) {
    this->dogs.push_back(dog);
    this->writeToFile();
}

void FileRepoShelterDogs::deleteDog(const std::string &name) {
    int position = this->getDogPositionByName(name);
    this->dogs.erase(this->dogs.begin()+position);
    this->writeToFile();
}



