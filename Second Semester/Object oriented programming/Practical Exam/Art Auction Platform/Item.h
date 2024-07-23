#pragma once
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>

using namespace std;

class Item {

private:
    std::string n;
    std::string c;
    int p;
    std::vector<tuple<int, std::string, int>> l;

public:
    explicit Item(std::string name="", std::string category="", int price=0, std::vector<tuple<int, std::string, int>> list={})
            : n(std::move(name)), c(std::move(category)), p(price), l{std::move(list)} {}



    std::string getName(){ return n; };
    std::string getCategory(){ return c; };
    int getPrice() { return p; };
    std::vector<tuple<int, std::string, int>> getList() {return l;};

    void setPrice(int newPrice){ this->p=newPrice;};
    void setList(std::vector<tuple<int, std::string, int>> newList){ this->l=newList;};
    friend istream& operator>>(istream& input, Item& item) {
            std::string name, category;
            int price;
            std::vector<tuple<int, std::string, int>> list;

            if (!(input >> name >> category >> price)) {
                return input;
            }

            char c;
            while (input >> c && c == '(') {
                int a, b, c;
                input >> a >> b >> c >> ws;
                std::string aa="";
                list.emplace_back(a, aa, c);
                if (!(input >> c && c == ')')) {
                    break;
                }
            }

            item = Item(name, category, price, list);

            return input;

    }


};


