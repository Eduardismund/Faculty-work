#include "Service.h"


std::vector<Package> Service::getAllPackages()
{
    std::vector<Package> allThemPackages= this->courierRepository.getAllPackages();
    std::vector<Courier> allThemCouriers= this->courierRepository.getAllCouriers();
    return allThemPackages;
}

std::vector<Courier> Service::getAllCouriers()
{
    std::vector<Package> allThemPackages= this->courierRepository.getAllPackages();
    std::vector<Courier> allThemCouriers= this->courierRepository.getAllCouriers();
    return allThemCouriers;
}

void Service::addPackage(Package p)
{
    std::vector<Package> allThemPackages= this->courierRepository.getAllPackages();
    std::vector<Courier> allThemCouriers= this->courierRepository.getAllCouriers();
    this->courierRepository.addPackage(p);
    this->notify();
}

void Service::addCourier(Courier c)
{
    std::vector<Package> allThemPackages= this->courierRepository.getAllPackages();
    std::vector<Courier> allThemCouriers= this->courierRepository.getAllCouriers();
    courierRepository.addCourier(c);
    this->notify();
}

void Service::deliverPackage(std::string sender, std::string address)
{
    std::vector<Package> allThemPackages= this->courierRepository.getAllPackages();
    std::vector<Courier> allThemCouriers= this->courierRepository.getAllCouriers();
    Package& p = courierRepository.getPackageBySenderAndAddress(sender, address);
    p.setStatus(true);
    this->notify();
}