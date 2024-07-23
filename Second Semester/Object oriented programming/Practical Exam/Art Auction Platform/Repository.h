#pragma once

#include <vector>
#include "Item.h"
#include "User.h"

using namespace std;

class Repository {

private:
    std::vector<Item> arrItem;
    std::vector<User> arrUser;

public:

    Repository() {
        this->readFromFileItems();
        this->readFromFileUsers();
    }

    std::vector<Item> &getItems() {return this->arrItem;};
    std::vector<User> &getUsers() {return this->arrUser;};

    void readFromFileItems();
    void readFromFileUsers();

    void saveToFileItems();
    void saveToFileUsers();

    std::vector<Item> sortByCategory(std::string cateogory);
    void addItem(Item item);
    std::vector<tuple<int, std::string, int>> getList(std::string name);
    void bid(std::string name, tuple<int, std::string, int> offer);


    ~Repository(){
        this->saveToFileItems();
        this->saveToFileUsers();
    }

};


