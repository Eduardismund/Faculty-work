#include "Service.h"
#include <fstream>

void Service::addBuilding(Building *building) {
    this->buildings.push_back(building);
}

void Service::writeToFile(std::string& filename1, std::string& filename2, std::vector<Building *> &buildings) {
    std::ofstream writeToFile1(filename1);
    writeToFile1<<"Buildings to be destroyed: \n";
    for(auto building: this->getAllToBeDemilished())
        writeToFile1<<building->toString()<<"\n";
    std::ofstream writeToFile12(filename2);
    writeToFile12<<"Buildings to be restored:\n";
    for(auto building2: this->getAllToBeRestored())
            writeToFile12<<building2->toString()<<"\n";
}

std::vector<Building *> Service::getAllBuildings() {
    return this->buildings;
}

std::vector<Building *> Service::getAllToBeDemilished() {
    std::vector<Building *> demolished;
    for(auto building: this->buildings)
        if(building->canBeDemolished())
            demolished.push_back(building);
    return demolished;
}


std::vector<Building *> Service::getAllToBeRestored() {
    std::vector<Building *> restored;
    for(auto building: this->buildings)
        if(building->mustBeRestored())
            restored.push_back(building);
    return restored;
}

std::vector<Building *> Service::getAllToBeDemilishedAfterAGiven(int year) {
    std::vector<Building *> demolished;
    for(auto building: this->getAllToBeDemilished())
        if(building->getYear() < year)
            demolished.push_back(building);
    return demolished;
}

void Service::generateEntries() {
    this->buildings.push_back(new Block("101_Scortarilor",2000, 120, 5));
    this->buildings.push_back(new Block("102_Siretului",1940, 50, 50));
    this->buildings.push_back(new House("101_Scortarilor",1890, true));
}
