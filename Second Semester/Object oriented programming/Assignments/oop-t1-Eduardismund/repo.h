///

#include "player.h"
#include <vector>

class Repo{
private:
    std::vector<Player> vectorWithPlayers;
public:
    Repo();
    ~Repo();
    Repo &operator=(const Repo &repository);
    void add(Player &player);
    int getIndex(Player &player);
    std::vector<Player> getVector();
};
