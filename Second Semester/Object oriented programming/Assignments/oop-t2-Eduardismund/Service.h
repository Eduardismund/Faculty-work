
#include <vector>
#pragma once
#include "house.h"

class Service{
private:
    std::vector<Building*> buildings;
public:
    Service(){
        this->generateEntries();
    }
    ~Service()=default;
    void addBuilding(Building *building);
    std::vector<Building *>getAllBuildings();
    std::vector<Building *>getAllToBeDemilished();
    std::vector<Building *>getAllToBeDemilishedAfterAGiven(int year);
    std::vector<Building *>getAllToBeRestored();
    void writeToFile(std::string& filename1, std::string &filename2, std::vector<Building *> &buildings);
    void generateEntries();
};

