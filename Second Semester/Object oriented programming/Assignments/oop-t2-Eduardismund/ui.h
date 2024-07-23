
#pragma once
#include "Service.h"

class UI{
private:
    Service service;
public:
    UI()=default;
    ~UI()=default;
    void addBuilding();
    void showAll();
    void showAllToBeDemolished();
    void writeToFile();
    void run();
};


