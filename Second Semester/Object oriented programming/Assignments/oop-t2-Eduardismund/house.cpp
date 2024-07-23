#include "house.h"

bool House::mustBeRestored() {
    return(2024-this->constructionYear>100);
}

bool House::canBeDemolished() {
    return !this->isHistorical;
}

std::string House::toString() {
    std::string s= "Type: House\nAddress: "+Building::toString()+"\n";
    if(this->isHistorical)
        return s+"Is historical\n";
    return s+"Is not historical\n";
}

