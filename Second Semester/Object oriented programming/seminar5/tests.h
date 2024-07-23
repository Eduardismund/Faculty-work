#pragma once
#include <vector>
#include "Exception.h"
#include "RepoShelterDogs.h"
#include "Dog.h"
#include "ServiceAdmin.h"
#include "RepoAdoptedDogs.h"
#include "ServiceUser.h"

class Test{
private:
    static void testDog();
    static void testShelterRepository();
    static void testAdminService();
    static void testAdoptedRepo();
    static void testUserService();
public:
    void testAll();
};