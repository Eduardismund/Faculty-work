#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {

private:
    std::string n;
    int id;
    std::string t;

public:
    explicit User(std::string name="", int id=0, std::string type="")
            : n{ std::move(name) }, t{ std::move(type) }, id{ id } {}

    std::string getName() {return n;};
    int getId() {return id;}
    std::string getType() { return t; };

    friend istream& operator>>(istream& input, User& user){
        std::string name, type;
        int id;

        if (!(input >> name >> id >> type)) {
            return input;
        }

        user = User(name, id, type);

        return input;
    }
};

