#include "ui.h"
#include <iostream>

UI::UI() {
    this->service = Service();
}

UI::~UI() = default;

void UI::printMenu() {
    std::cout<<"1. Add a new player\n";
    std::cout<<"2. display all players\n";
    std::cout<<"3. display all players for a given team \n";
    std::cout<<"4. exit \n\n";
}

void UI::displayAllPlayer() {
    std::vector<Player> allPlayers = this->service.getAllPlayers();
    for(int i = 0; i<allPlayers.size();i++)
        std::cout<<allPlayers[i].getName()<<" | "<<allPlayers[i].getNationality()<<" | "<<allPlayers[i].getTeam()<<" | "<<allPlayers[i].getGoals()<<" \n";

}

void UI::displayAllPlayersGivenTeam() {
    std::string team;
    std::cout<<"Insert a team name: ";
    std::cin>>team;
    std::vector<Player> allPlayers = this->service.getPlayersGivenTeam(team);
    if(allPlayers.empty())
        std::cout<<"No players for this team!\n\n";
    else
        for(int i = 0; i<allPlayers.size();i++)
            std::cout<<allPlayers[i].getName()<<" | "<<allPlayers[i].getNationality()<<" | "<<allPlayers[i].getTeam()<<" | "<<allPlayers[i].getGoals()<<"\n";
    int no_of_goals = this->service.totalNumberOfGoals(team);
    if(no_of_goals == 0)
        std::cout<<"No goals for this team!\n";
    else
        std::cout<<"The team "<< team<< " had a performance of "<< no_of_goals<< " goals!\n";

}
void UI::addPlayer() {
    std::string name, nationality, team, goals;
    std::cout<<"Insert a name: ";
    std::cin>>name;
    std::cout<<"Insert a nationality: ";
    std::cin>>nationality;
    std::cout<<"Insert a team: ";
    std::cin>>team;
    std::cout<<"Insert the number of goals: ";
    std::cin>>goals;
    if(goals.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout<<"Goals must be a positive number!\n";
        this->run();
    }

    int g = stoi(goals);
    if(this->service.addToRepo(name, nationality, team, g))
        std::cout<<"\nPlayer added successfully!\n";
    else
        std::cout<<"\nCannot add player!\nOne with the same name already exists!\n";
}

void UI::run(){
    int command;
    while(true) {
        std::cout<<"\n";
        this->printMenu();
        std::cout << "Insert command: ";
        std::cin >> command;
        if (command == 1)
            this->addPlayer();
        else if (command == 2)
            this->displayAllPlayer();
        else if (command == 3)
            this->displayAllPlayersGivenTeam();
        else if (command == 4)
            break;
        else
            std::cout<<"Insert a valid command!\n";

    }
}

