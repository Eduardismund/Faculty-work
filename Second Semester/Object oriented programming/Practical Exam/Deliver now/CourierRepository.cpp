#include "CourierRepository.h"
#include <string>

CourierRepository::CourierRepository()
{
    loadCouriersFromFile("couriers.txt");
    loadPackagesFromFile("packages.txt");
}

// Method to load couriers from file
void CourierRepository::loadCouriersFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line))
    {
        Courier c = parseCourier(line);
        couriers.push_back(c);
    }
}

// Method to load packages from file
void CourierRepository::loadPackagesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line))
    {
        Package p = parsePackage(line);
        packages.push_back(p);
    }
}

std::vector<Courier> CourierRepository::getAllCouriers()
{
	return this->couriers;
}

void CourierRepository::addCourier(Courier c)
{
	this->couriers.push_back(c);
}

//complete this function to parse couriers from couriers.txt using variables from courier.h
Courier CourierRepository::parseCourier(std::string line)
{
    std::stringstream ss(line);
    std::string token;

    // Parse name
    std::getline(ss, token, '|');
    std::string name = token;

    // Parse streets
    std::getline(ss, token, '|');
    std::stringstream streetStream(token);
    std::vector<std::string> streets;
    std::string street;
    while (std::getline(streetStream, street, ';'))
    {
        streets.push_back(street);
    }

    // Parse zone c
    std::getline(ss, token, '|');
    int c = std::stoi(token);

    // Parse zone r
    std::getline(ss, token, '|');
    int r = std::stoi(token);

    Zone zone{c, r};

    return Courier(name, streets, zone);
}



std::vector<Package> CourierRepository::getAllPackages()
{
    return this->packages;
}

//add a package to the vector of packages
void CourierRepository::addPackage(Package p)
{
    this->packages.push_back(p);
}

Package CourierRepository::parsePackage(std::string line)
{
    std::stringstream ss(line);
    std::string token;

    std::getline(ss, token, '|');
    std::string recipient = token;

    std::getline(ss, token, '|');
    std::string address = token;

    std::getline(ss, token, '|');
    int locationX = std::stoi(token);

    std::getline(ss, token, '|');
    int locationY = std::stoi(token);

    std::getline(ss, token, '|');
    bool status = (token == "true");

    Location location{locationX, locationY};

    return Package(recipient, address, location, status);
}


//get a package by sender and address
Package& CourierRepository::getPackageBySenderAndAddress(std::string sender, std::string address)
{
    for (auto& p : this->packages)
    {
        if (p.getRecipient() == sender && p.getAddress() == address)
        {
            p.setStatus(true);
            return p;
        }
    }
    throw std::runtime_error("Package not found");
}