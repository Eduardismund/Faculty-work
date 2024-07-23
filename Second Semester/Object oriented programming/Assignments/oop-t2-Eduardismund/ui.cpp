
#include "ui.h"
#include <iostream>

void UI::addBuilding() {
    std::string type;
    std::cout<<"Insert the type of building you want to add: ";
    std::cin>>type;
    if(type=="Block"){
        int totalApartments, occupiedApartments;
        std::string address;
        int constructionYear;
        std::cout<<"Insert an address(separated by _): ";
        std::cin>>address;
        std::cout<<"Insert a construction year: ";
        std::cin>>constructionYear;
        std::cout<<"Insert a total number of apartments: ";
        std::cin>>totalApartments;
        std::cout<<"Insert the number of apartments in usage: ";
        std::cin>>occupiedApartments;
        this->service.addBuilding(new Block(address, constructionYear, totalApartments, occupiedApartments));
        std::cout<<"Block added successfully!\n";
    }
    else if(type=="House")
    {
        bool isHistorical;
        std::string address, answer;
        int constructionYear;
        std::cout<<"Insert an address(separated by _): ";
        std::cin>>address;
        std::cout<<"Insert a construction year: ";
        std::cin>>constructionYear;
        std::cout<<"Is the house historical? ";
        std::cin>>answer;
        if(answer=="yes")
            isHistorical=true;
        else
            isHistorical=false;
        this->service.addBuilding(new House(address, constructionYear, isHistorical));
        std::cout<<"House added successfully!\n";
    }
    else
        std::cout<<"Not a valid type of building!\n";
}

void UI::writeToFile() {
    std::string s="destroyed.txt";
    std::string s2="restored.txt";
    std::vector<Building *>buildings= this->service.getAllBuildings();
    this->service.writeToFile(s, s2, buildings);
    std::cout<<"Saved to files successfully!\n";
}

void UI::showAll() {
    for(auto building: this->service.getAllBuildings())
        std::cout<<building->toString()<<"\n";
}

void UI::showAllToBeDemolished() {
    int year;
    std::cout<<"Insert a year: ";
    std::cin>>year;
    for(auto building: this->service.getAllToBeDemilishedAfterAGiven(year))
        std::cout<<building->toString()<<"\n";
}

void UI::run() {
    int command;
    while(true)
    {
        std::cout<<"1. Add a building\n2.Show all buildings\n3.Show buildings that can be demolished older than a given year\n4. Save to file the buildings to be demolished and the ones to be restored.\n5.Exit\n";
        std::cout<<"Insert a command: ";
        std::cin>>command;
        std::cout<<"\n";
        if(command==1)
            this->addBuilding();
        else if(command==2)
            this->showAll();
        else if(command==3)
            this->showAllToBeDemolished();
        else if(command==4)
            this->writeToFile();
        else if(command==5)
            break;
        else
            std::cout<<"Incorrect option!\n";
    }
}
