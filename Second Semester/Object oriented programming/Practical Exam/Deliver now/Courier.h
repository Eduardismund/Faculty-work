#pragma once

#include <string>
#include <vector>
#include "Package.h"

using namespace std;

struct Zone {
    int c, r;
};

class Courier
{
public:
    explicit Courier(string name = "", vector<string> streets = {}, Zone zone = {0, 0})
            : name{std::move(name)}, streets{std::move(streets)}, zone{zone} {}

    string getName() const {
        return name;
    }

    vector<string>& getStreets() {
        return streets;
    }

    Zone getZone() const {
        return zone;
    }

    bool isWithinZone(const Location& location) const {
        int dx = location.xCoordinate - zone.c;
        int dy = location.yCoordinate - zone.c;
        int distanceSquared = dx * dx + dy * dy;
        int radiusSquared = zone.r * zone.r;
        return distanceSquared <= radiusSquared;
    }

    ~Courier() = default;

private:
    string name;
    vector<string> streets;
    Zone zone;
};
