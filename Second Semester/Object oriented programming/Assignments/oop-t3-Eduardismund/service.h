
#pragma once
#include "repository.h"
#include <algorithm>

class service {
private:
    repository r;
public:
    std::vector<Equation> getAllEqs();
    void updateEq(int oldA, int oldB, int oldC,int a, int b, int c);
    std::string computeSol(Equation eq);

};
