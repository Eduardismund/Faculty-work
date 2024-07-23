#include "service.h"
#pragma once

class UI{
private:
    Service service;
public:
    UI();
    ~UI();
    void printMenu();
    void run();
    void addPlayer();
    void displayAllPlayer();
    void displayAllPlayersGivenTeam();
};
