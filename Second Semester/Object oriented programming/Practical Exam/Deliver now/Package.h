#pragma once

#include <string>
#include <iostream>
using namespace std;

struct Location {
    int xCoordinate;
    int yCoordinate;
};

class Package
{
private:
    string recipient;
    string address;
    Location location;
    bool status;

public:
    explicit Package(string recipient = "", string address = "", const Location& location = {0, 0}, bool status = false)
            : recipient{std::move(recipient)}, address{std::move(address)}, location{location}, status{status} {}

    string getRecipient() const {
        return this->recipient;
    }

    string getAddress() const {
        return this->address;
    }

    Location getLocation() const {
        return this->location;
    }

    bool getStatus() const {
        return this->status;
    }

    void setStatus(bool status) {
        this->status = status;
    }

    string toString() const {
        return this->getRecipient() + " - " + this->getAddress();
    }

    friend ostream& operator<<(ostream& os, const Package& package) {
        os << "Recipient: " << package.getRecipient() << ", Address: " << package.getAddress()
           << ", Location: (" << package.getLocation().xCoordinate << ", " << package.getLocation().yCoordinate << ")"
           << ", Status: " << (package.getStatus() ? "Delivered" : "Not Delivered");
        return os;
    }

    friend istream& operator>>(istream& is, Package& package) {
        string recipient, address;
        Location location;
        bool status;
        char comma;
        if (is >> std::ws && std::getline(is, recipient, ',') && std::getline(is, address, ',') &&
            is >> location.xCoordinate >> comma >> location.yCoordinate >> comma >> status) {
            package.recipient = std::move(recipient);
            package.address = std::move(address);
            package.location = location;
            package.status = status;
        }
        return is;
    }
};
