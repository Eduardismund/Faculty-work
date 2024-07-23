
#include "Service.h"
#include <algorithm>


Service::Service() : repo(){

}

std::vector<Item> &Service::getItems() {
    std::vector<Item> &arr = repo.getItems();
    std::sort(arr.begin(), arr.end(), [](Item& a, Item& b) {
        return a.getPrice() < b.getPrice();
    });
    return arr;
}

std::vector<User> &Service::getUsers() {
    std::vector<User> &users = repo.getUsers();

    return users;
}



std::vector<Item> Service::sortByCategory(std::string cateogory) {
    std::vector<Item> &arr = repo.getItems();
    std::vector<User> &users = repo.getUsers();
    return repo.sortByCategory(cateogory);
}

void Service::addItem(Item item) {
    std::vector<Item> &arr = repo.getItems();
    std::vector<User> &users = repo.getUsers();
    repo.addItem(item);
    notifyAllObservables();


}

std::vector<tuple<int, std::string, int>> Service::getList(std::string name) {
    std::vector<Item> &arr = repo.getItems();
    std::vector<User> &users = repo.getUsers();
    return repo.getList(name);
}

void Service::bid(std::string name, tuple<int, std::string, int> offer) {
    std::vector<Item> &arr = repo.getItems();
    std::vector<User> &users = repo.getUsers();
    repo.bid(name, offer);

}
