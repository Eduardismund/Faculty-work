#pragma once
#include "ServiceAdmin.h"
#include "ServiceUser.h"

class UI{
private:
    AdminService& serviceForAdmin;
    ServiceUser& serviceForUser;
public:
    UI(AdminService& serviceForAdminToBeSet, ServiceUser& serviceForUserToBeSet);
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