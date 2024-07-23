#pragma once
#include "repo.h"

class Service{
private:
    Repo repository;
public:
    Service();
    ~Service();
    Service& operator=(const Service &service);
    bool addToRepo(std::string &name, std::string &nationality, std::string &team, int goals);
    std::vector<Player> getAllPlayers();
    std::vector<Player> getPlayersGivenTeam(std::string &team);
    int totalNumberOfGoals(std::string &team);
};
