
#include "building.h"
#pragma once


class House: public Building{
private:
    bool isHistorical;
public:
    explicit House(std::string address="", int constructionYear=0, bool isHistorical=false): Building{std::move(address), constructionYear}, isHistorical{isHistorical}{};
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};




