#pragma once
#include "equations.h"
#include <vector>
#include <fstream>
#include <sstream>


class repository {
private:
    std::vector<Equation> eqs;
public:
    repository(){this->loadFile();};
    void loadFile();
    std::vector<Equation>& getEqs();
};

