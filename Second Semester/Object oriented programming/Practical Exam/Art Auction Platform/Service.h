#pragma once

#include "Repository.h"
#include "Observer.h"

class Service : public Subject {

private:
    Repository repo;

public:
    Service();

    std::vector<Item> &getItems();
    std::vector<User> &getUsers();



    std::vector<Item> sortByCategory(std::string cateogory);
    void addItem(Item item);
    std::vector<tuple<int, std::string, int>> getList(std::string name);
    void bid(std::string name, tuple<int, std::string, int> offer);

};
