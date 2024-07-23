#include "service.h"
#include <algorithm>

Service::Service() {
    this->repository = Repo();
}

Service::~Service() = default;

Service &Service::operator=(const Service &service) {
    this->repository = service.repository;
    return *this;
}

///bool function that returns true if the player has been added successfully and false if the player
///alreday exists. this check is done by the 'getIndex' method. the player is composed from: the name,
///the nationality, the team and the goals
bool Service::addToRepo(std::string &name, std::string &nationality, std::string &team, int goals) {
    Player p = Player(name, nationality, team, goals);
    int index = this->repository.getIndex(p);
    if(index != -1 and !this->repository.getVector().empty())
        return false;
    this->repository.add(p);
    return true;
}

std::vector<Player> Service::getAllPlayers() {
    return this->repository.getVector();
}


///this function returns the vector with players for a given team. we first iterate through the vectorOfPlayers
///that was recieved from the repo, then we check at each step if the name of the team coincides with the one of
///the player. in that case we add it to the filtered vector
///in the second part we sort it using the 'std::sort' having as filter the number of goals
std::vector<Player> Service::getPlayersGivenTeam(std::string &team) {
    std::vector<Player> vectorOfPlayers = this->repository.getVector();
    std::vector<Player> vectorOfPlayersGivenTeam;
    for(int i=0; i<vectorOfPlayers.size();i++)
        if(vectorOfPlayers[i].getTeam() == team)
            vectorOfPlayersGivenTeam.push_back(vectorOfPlayers[i]);
    std::sort(vectorOfPlayersGivenTeam.begin(), vectorOfPlayersGivenTeam.end(), [](Player a, Player b) {
        return a.getGoals()<b.getGoals();
    });
    return vectorOfPlayersGivenTeam;
}

///we iterate again through the vector and search for the given team/ we increase the number of goals
/// ///then and return it
int Service::totalNumberOfGoals(std::string &team) {
    std::vector<Player> vectorOfPlayers = this->repository.getVector();
    int g = 0;
    for(int i=0; i<vectorOfPlayers.size();i++)
        if(vectorOfPlayers[i].getTeam() == team)
            g += vectorOfPlayers[i].getGoals();
    return g;
}