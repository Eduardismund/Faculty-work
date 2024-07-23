
#include <iostream>
#include "repository.h"

void repository::loadFile() {
    std::ifstream file("equ.txt");
    const char delimiter=',';
    std::string line;
    std::string a,b,c;
    int ai, bi, ci;
    while(std::getline(file,line))
    {
        std::istringstream iss(line);
        std::getline(iss, a, delimiter);
        std::getline(iss, b, delimiter);
        std::getline(iss, c, delimiter);
        ai=stoi(a);
        bi=stoi(b);
        ci=stoi(c);

        this->eqs.emplace_back(ai,bi,ci);
    }
}

std::vector<Equation>& repository::getEqs() {
    return this->eqs;
}
