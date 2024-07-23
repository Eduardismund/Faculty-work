#pragma once
#include <string>

class Player{
private:
    std::string name;
    std::string nationality;
    std::string team;
    int goals;
public:
    Player(const std::string &name, const std::string &nationality, const std::string &team, int goals);
    Player(const Player &player);
    ~Player();

    std::string getName();
    std::string getNationality();
    std::string getTeam();
    int getGoals();
    bool operator==(const Player &player) const;


};