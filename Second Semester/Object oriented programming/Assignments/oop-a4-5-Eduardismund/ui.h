#pragma once
#include "AdminService.h"
#include "UserService.h"

class UI{
private:
    AdminService& serviceForAdmin;
    UserService& serviceForUser;
public:
    UI(AdminService& serviceForAdminToBeSet, UserService& serviceForUserToBeSet);
    ~UI();

    //start the app
    void run();
    void chooseMode();
    static void printMenu();

    //admin mode
    void startAdmin();
    static void printAdminMenu();

    //user mode
    void startUser();
    static void printUserMenu();

    static void printFilteredDogs();
    void generateEntries();
};