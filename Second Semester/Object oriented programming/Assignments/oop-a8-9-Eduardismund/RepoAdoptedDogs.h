#pragma once
#include "Dog.h"
#include <vector>
#include "sqlite3.h"
//#include <sqlite3.h>

class RepoAdoptedDogs{
private:
    std::vector<Dog> vectorWithAdoptedDogs;
public:
//    RepoAdoptedDogs();
//    ~RepoAdoptedDogs();

    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    virtual void addAdoption(const Dog &dog);
    std::vector<Dog> getAdoption();

    virtual void write() = 0;

    virtual void display() {};

};

class RepoAdoptedDogsCSV : public RepoAdoptedDogs {
public:

    void write() override;

    void display() override;

};

class RepoAdoptedDogsHTML : public RepoAdoptedDogs {
public:

    void write() override;

    void display() override;
};
