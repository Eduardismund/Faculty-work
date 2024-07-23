
#include "player.h"

Player::Player(const std::string &name, const std::string &nationality, const std::string &team, int goals) {
    this->name = name;
    this->nationality = nationality;
    this->team = team;
    this->goals = goals;
}

Player::Player(const Player &player) = default;

Player::~Player() = default;

std::string Player::getName() {
    return this->name;
}

int Player::getGoals() {
    return this->goals;
}

std::string Player::getNationality() {
    return this->nationality;
}

std::string Player::getTeam() {
    return this->team;
}

bool Player::operator==(const Player &player) const {
    return this->name == player.name;
}

