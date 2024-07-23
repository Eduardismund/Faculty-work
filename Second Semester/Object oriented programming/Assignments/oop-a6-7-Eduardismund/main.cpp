#include "ServiceAdmin.h"
#include "UserInterface.h"
#include "tests.h"
//#include <crtdbg.h>
#include "ServiceUser.h"
#include <iostream>
using namespace std;

int main()
{
//    Test tests;
//    tests.testAll();

    RepoShelterDogs *repoShelter = nullptr;
    RepoAdoptedDogs *repoAdoption = nullptr;
    {
        cout << "Which type of file do you want to use for User Moder? (CSV/HTML): ";
        string fileType1;
        cin >> fileType1;
        if (fileType1 == "CSV") {
            repoAdoption = new RepoAdoptedDogsCSV;
        } else {
            repoAdoption = new RepoAdoptedDogsHTML;
        }
    }
    {
        cout << "Which type of file do you want to use for Admin Mode? (File/Database): ";
        string fileType2;
        cin >> fileType2;
        if (fileType2 == "File") {
            repoShelter = new FileRepoShelterDogs;
        } else {
            repoShelter = new DBRepository;
        }
    }
    ServiceUser userService(repoShelter, repoAdoption);
    AdminService serviceAdmin(repoShelter);

    UI ui(serviceAdmin, userService);
    ui.run();
    //_CrtDumpMemoryLeaks();
    return 0;
}