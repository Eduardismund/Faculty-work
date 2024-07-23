#include "AdminService.h"
#include "ui.h"
#include "tests.h"
//#include <crtdbg.h>
#include "UserService.h"

int main()
{
    Test tests;
    tests.testAll();
    ShelterRepository repoShelter;
    AdoptedRepo repoAdoption;
    UserService userService(repoShelter,repoAdoption);
    AdminService serviceAdmin(repoShelter);

    UI ui(serviceAdmin, userService);
    ui.run();
    //_CrtDumpMemoryLeaks();
    return 0;
}