#pragma once
#include "CourierRepository.h"
#include <vector>
#include "Package.h"
#include "Courier.h"
#include "Observer.h"

class Service : public Signal
{
private:
	CourierRepository& courierRepository;
public:
	explicit Service(CourierRepository& courierRepository):courierRepository{ courierRepository } {}
	std::vector<Package> getAllPackages();
	std::vector<Courier> getAllCouriers();
	void addPackage(Package p);
	void addCourier(Courier c);
	void deliverPackage(std::string sender, std::string address);
	~Service() = default;
};

