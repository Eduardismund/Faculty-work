#include <iostream>
#include <QPainter>
//#include "UserInterface.h"
#include "GUI.h"
using namespace std;

int main(int argc, char* argv[])
{
//    Test tests;
//    tests.testAll();

    /// Initialize the repositories
    RepoShelterDogs *repoShelter = nullptr;
    RepoAdoptedDogs *repoAdopted = nullptr;

    /// Initialize the services
    AdminService serviceAdmin(repoShelter);
    ServiceUser serviceUser(repoShelter, repoAdopted);

    /// Initialize the GUI
    QApplication app(argc, argv);
    GUI gui(serviceAdmin, serviceUser);

    /// Show the GUI
    gui.show();

    return app.exec();
}