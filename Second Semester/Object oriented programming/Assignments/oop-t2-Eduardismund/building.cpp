#include "building.h"

std::string Building::toString() {
    return "Address: "+this->address+"\nConstruction year: "+std::to_string(this->constructionYear);
}

bool Block::mustBeRestored() {
    return (2024-this->constructionYear>40 && this->occupiedApartments*100/this->totalApartments>80);
}

bool Block::canBeDemolished() {
    return (this->occupiedApartments*100/this->totalApartments<5);
}



std::string Block::toString() {
    return "Type: Block\n" + Building::toString() +"\nTotal apartments: "+std::to_string(this->totalApartments)+"\nOccupied apartments: "+std::to_string(this->occupiedApartments)+"\n";
}
