#pragma once
#include <vector>
#include "Courier.h"
#include <fstream>
#include <sstream>

class CourierRepository
{
private:
	std::vector<Courier> couriers;
	std::string filename = "couriers.txt";
    std::vector<Package> packages;
    std::string filename1 = "packages.txt";
public:
	CourierRepository();
    void loadCouriersFromFile(const std::string& filename);
    void loadPackagesFromFile(const std::string& filename);
    std::vector<Package> getAllPackages();
    void addPackage(Package p);
    Package parsePackage(std::string line);
    Package& getPackageBySenderAndAddress(std::string sender, std::string address);
	std::vector<Courier> getAllCouriers();
	void addCourier(Courier c);
	Courier parseCourier(std::string line);
	~CourierRepository() = default;
};

