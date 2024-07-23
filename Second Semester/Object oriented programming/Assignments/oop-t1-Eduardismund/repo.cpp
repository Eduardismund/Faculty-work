
#include "repo.h"

Repo::Repo() {
    this->vectorWithPlayers = std::vector<Player>();
    Player p1 = Player("Nora_Mork", "NOR", "Larvik", 83);
    Player p2 = Player("Isabelle_Gulden", "SWE", "CSM_Bucarest", 80);
    Player p3 = Player("Cristina_Neagu", "ROU", "Buducnost", 63);
    Player p4 = Player("Ilina_Ekaterina", "RUS", "Rostov-Don", 80);
    Player p5 = Player("Allison_Pineau", "FRA", "Larvik", 82);
    Player p6 = Player("Nerea_Pena", "ESP", "FTC-Rail_Cargo_Hungaria", 59);
    this->vectorWithPlayers.push_back(p1);
    this->vectorWithPlayers.push_back(p2);
    this->vectorWithPlayers.push_back(p3);
    this->vectorWithPlayers.push_back(p4);
    this->vectorWithPlayers.push_back(p5);
    this->vectorWithPlayers.push_back(p6);
}

Repo &Repo::operator=(const Repo &repository){
    this->vectorWithPlayers = repository.vectorWithPlayers;
    return *this;
}

Repo::~Repo() = default;


///adds the the object 'player' to the repository using the 'push_back' command of the
///stl 'vector'
void Repo::add(Player &player) {
    this->vectorWithPlayers.push_back(player);
}


///the vector where players are stored is returned by this function
std::vector<Player> Repo::getVector() {
    return this->vectorWithPlayers;
}

int Repo::getIndex(Player &player) {
    for (int i = 0; i < this->vectorWithPlayers.size(); i++)
        if (this->vectorWithPlayers[i] == player)
            return i;
    return -1;
}
