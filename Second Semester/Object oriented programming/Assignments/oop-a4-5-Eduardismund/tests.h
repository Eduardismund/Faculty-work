#pragma once
#include "DynamicArray.h"
#include "Exception.h"
#include "ShelterRepository.h"
#include "Dog.h"
#include "AdminService.h"
#include "AdoptedRepo.h"
#include "UserService.h"

class Test{
private:
    static void testDynamicVector();
    static void testDog();
    static void testShelterRepository();
    static void testAdminService();
    static void testAdoptedRepo();
    static void testUserService();
public:
    void testAll();
};