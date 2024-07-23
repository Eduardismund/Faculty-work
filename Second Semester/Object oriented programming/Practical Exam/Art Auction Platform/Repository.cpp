

#include <fstream>
#include <sstream>
#include "Repository.h"


void Repository::readFromFileItems() {
    std::ifstream file("items.txt");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> items;
        char delim = ',';
        std::stringstream ss(line);
        std::string current;
        while (std::getline(ss, current, delim)) {
            items.push_back(current);
        }

        if (items.size() < 3) {
            continue;
        }

        std::vector<std::tuple<int, std::string, int>> list;
        for (size_t i = 3; i + 2 < items.size(); i += 3) {
            list.emplace_back(std::stoi(items[i]), items[i + 1], std::stoi(items[i + 2]));
        }

        Item item(items[0], items[1], std::stoi(items[2]), list);
        arrItem.push_back(item);
    }

    file.close();
}

void Repository::readFromFileUsers() {
    ifstream file("users.txt");

    std::string line;
    while(getline(file, line))
    {
        std::vector <std::string> items;
        char delim= ',';
        stringstream ss{line};
        std::string current;
        while (getline(ss, current, delim))
        {
            items.push_back(current);
        }
        arrUser.emplace_back(items[0], stoi(items[1]), items[2]);
    }
    file.close();

}


void Repository::saveToFileItems() {
    ofstream g("items.txt");
    for(auto i:arrItem)
    {
        g<<i.getName()<<","<<i.getCategory()<<","<<i.getPrice()<<",";
        for(auto j:i.getList())
            g<<get<0>(j)<<","<<get<1>(j)<<","<<get<2>(j)<<",";
        g<<'\n';
    }
    g.close();

}

void Repository::saveToFileUsers() {
    ofstream g("users.txt");
    for(auto i:arrUser) {
        g << i.getName() << "," << i.getId() << "," << i.getType()<<'\n';
    }
    g.close();

}

std::vector<Item> Repository::sortByCategory(std::string category) {
    std::vector<Item> arr;
    std::vector<Item> all=this->arrItem;
    int j=0;
    for(auto i:all)
    {
        j++;
        if(i.getCategory() == category)
            arr.push_back(i);
    }
    return arr;
}

void Repository::addItem(Item item) {
    std::vector<Item> arr;
    std::vector<Item> all=this->arrItem;
    arrItem.push_back(item);

}

std::vector<tuple<int, std::string, int>> Repository::getList(std::string name) {
    std::vector<Item> arr;
    std::vector<Item> all=this->arrItem;
    for(auto i:all)
        if(i.getName() == name)
            return i.getList();
    return {};
}

void Repository::bid(std::string name, tuple<int, std::string, int> offer) {
    std::vector<Item> arr;
    std::vector<Item> all=this->arrItem;
    for(auto i:all)
    {
        if(i.getName() == name) {
            i.setPrice(get<2>(offer));
            std::vector<tuple<int, std::string, int>> list = i.getList();
            list.push_back(offer);
            i.setList(list);
        }

    }

}
