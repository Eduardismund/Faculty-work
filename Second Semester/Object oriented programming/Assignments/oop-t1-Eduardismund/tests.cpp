
#include "tests.h"
#include "cassert"

void tests::testAdd() {
    Service service;
    assert(service.getAllPlayers().size() == 6);
    std::string nume = "Edi", nat = "ROU", team = "Dinamo";
    assert(service.addToRepo(nume, nat, team, 60)==1);
    assert(service.getAllPlayers().size() == 7);

    assert(service.addToRepo(nume, nat, team, 60)==0);
    assert(service.getAllPlayers().size() == 7);
}

void tests::testName() {
    Service service;
    std::string nume = "Edi", nat = "ROU", team1 = "Dinamo";
    std::string nume2 = "ana";
    service.addToRepo(nume, nat, team1, 3);
    service.addToRepo(nume2, nat, team1, 2);
    std::vector<Player> goals = service.getPlayersGivenTeam(team1);
    assert(goals.size() == 2);

    assert(goals[0].getTeam() == "Dinamo");
    assert(goals[1].getTeam() == "Dinamo");

    assert(goals[0].getGoals() == 2);
    assert(goals[1].getGoals() == 3);

    assert(service.totalNumberOfGoals(team1) == 5);
}

void tests::TestAll() {
    testAdd();
    testName();
}



