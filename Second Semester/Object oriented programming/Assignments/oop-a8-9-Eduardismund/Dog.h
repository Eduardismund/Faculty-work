#pragma once

#include <string>
#include <regex>


class Dog{
private:
    std::string breed;
    std::string name;
    std::string photograph;
    int age;
public:
    Dog();
    Dog(const std::string &breed, const std::string &name, const std::string &photograph, int age);
    Dog(const Dog& otherDog);
    ~Dog();
    Dog& operator=(const Dog& otherDog);
    //Getters
    std::string getBreed() const;
    std::string getName() const;
    std::string getPhotograph() const;
    int getAge() const;
    //Setters
    void setBreed(const std::string &newBreed);
    void setName(const std::string &newName);
    void setPhotograph(const std::string &newPhotograph);
    void setAge(int newAge);
    bool operator==(const Dog& otherDog) const;

    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
    friend std::istream& operator>>(std::istream& is, Dog& dog);
};

class DogValidator {
public:
    static bool validateAge(const std::string& stringAge);
};