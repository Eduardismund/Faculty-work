#pragma once

#include "ServiceAdmin.h"
#include "ServiceUser.h"
#include <vector>
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPainter>
#include <QShortcut>
#include <QKeySequence>
#include <QAbstractTableModel>
#include <vector>
#include "TabelList.h"

class GUI : public QWidget{
    //inherits from QObject
private:

    ServiceUser& serviceUser;
    AdminService& adminService;

    //first page
    QPushButton* adminModeButton{};
    QPushButton* userModeButton{};
    QPushButton* bonusButton{};
    QPushButton* tableButton{};

    //second page for user
    QPushButton* csvButton{};
    QPushButton* htmlButton{};

    //second page for admin
    QPushButton* databaseButton{};
    QPushButton* fileTextButton{};

    ///---admin mode---
    QWidget* adminWidget{};
    QWidget* adminFileWidget{};

    //buttons for admin mode
    QPushButton* addDogButton{};
    QPushButton* removeDogButton{};
    QPushButton* updateButton{};
    QPushButton* saveAndExitButton{};
    QPushButton* undoButton{};
    QPushButton* redoButton{};
    QShortcut* undoShortcut{};
    QShortcut* redoShortcut{};

    //lines edit for adding info for the add, update and remove operations
    QLineEdit* nameLineEdit{};
    QLineEdit* breedLineEdit{};
    QLineEdit* ageLineEdit{};
    QLineEdit* photoLineEdit{};

    ///--user mode--
    QWidget* userWidget{};
    QWidget* userFileWidget{};

    /// buttons for the user mode
    QPushButton* showPhotoButton{};
    QPushButton* nextDogButton{};
    QPushButton* adoptDogButton{};
    QPushButton* seeAdoptedDogsButton{};
    QPushButton* saveAndExitUserButton{};
    QPushButton* seeFilteredDogsButton{};


    /// labels for the dog data
    QLabel* nameLabelInfo{};
    QLabel* breedLabelInfo{};
    QLabel* ageLabelInfo{};
    QLabel* photoLabelInfo{};

    ///for the chart bonus

    QWidget* bonusWidget{};

    QWidget* tableWidget{};

    /// widgets for all application
    QListWidget* dogsListWidget{};

    std::vector<Dog> dogList;
public:
    // constructor
    GUI(AdminService& serviceAdminToBeSet, ServiceUser& serviceUserToBeSet, QWidget* parent = Q_NULLPTR);

    // destructor
    ~GUI() override;

    /// admin mode
    void AdminModeGUI();

    void chooseAdminFileType();

    void setTextFile();
    void setDatabaseFile();

    void addDogGUI();
    void deleteDogGUI();
    void updateDogGUI();
    void saveAndExitAdminGUI();
    void executeUndo();
    void executeRedo();

    void populateListAdminMode();
    void showDogDataAdmin();
    void applyStyles();

    /// user mode
    void chooseUserFileType();

    void setCSVFile();
    void setHTMLFile();

    void UserModeGUI();

    void populateListUserMode();

    [[maybe_unused]] void showDogDataUser();

    void showPhoto();
    void nextDogGUI();
    void adoptDogGUI();
    void seeAdoptedDogsGUI();
    void filterDogsGUI();

    void saveAndExitUserGUI();

    ///bonus mode

    void bonusModeGUI();
    void saveAndExitBonusGUI();

    void tableModeGUI();
    void saveAndExitTableGUI();


};

