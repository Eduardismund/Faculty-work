#include "GUI.h"
#include <algorithm>
#include <cmath>
#include <iostream>


GUI::GUI(AdminService &serviceAdminToBeSet, ServiceUser &serviceUserToBeSet, QWidget *parent): QWidget(parent),
                                                                                               adminService(serviceAdminToBeSet),
                                                                                               serviceUser(serviceUserToBeSet)
{


    auto* firstPageLayout = new QVBoxLayout{this};

    this->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    this->setWindowIcon(QIcon(R"(C:\Users\User\CLionProjects\oop-a8-9-Eduardismund\project.png)"));
    this->setMinimumSize(850, 200);

    /// welcome label
    QFont font("Verdana", 20, QFont::Bold);
    auto* welcomeLabel = new QLabel("Welcome to the Keep Calm and Adopt a Dog Shelter!", this);
    welcomeLabel->setFont(font);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    firstPageLayout->addWidget(welcomeLabel);



    // buttons
    auto* buttonsLayout = new QHBoxLayout{};

    QFont fontModes("Arial", 15, QFont::Bold);

    this->adminModeButton = new QPushButton("Admin mode");
    this->adminModeButton->setFont(fontModes);

    this->userModeButton = new QPushButton("User mode");
    this->userModeButton->setFont(fontModes);

    this->bonusButton = new QPushButton("Bonus-Chart view");
    this->bonusButton->setFont(fontModes);

    this->tableButton = new QPushButton("Table view");
    this->tableButton->setFont(fontModes);

    buttonsLayout->addWidget(this->adminModeButton);
    buttonsLayout->addWidget(this->userModeButton);
    buttonsLayout->addWidget(this->bonusButton);
    buttonsLayout->addWidget(this->tableButton);
    // add the buttons layout to the main layout
    firstPageLayout->addLayout(buttonsLayout);

    // connect the signals and slots
    QObject::connect(this->adminModeButton, &QPushButton::clicked, this, &GUI::chooseAdminFileType);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::chooseUserFileType);
    QObject::connect(this->bonusButton, &QPushButton::clicked, this, &GUI::bonusModeGUI);
    QObject::connect(this->tableButton, &QPushButton::clicked, this, &GUI::tableModeGUI);
    this->applyStyles();

}

void GUI::applyStyles() {

    this->setStyleSheet("background-color: #f0f0f0;");


    QString buttonStyle = "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
                          "QPushButton:hover { background-color: #45a049; }";
    this->adminModeButton->setStyleSheet(buttonStyle);
    this->userModeButton->setStyleSheet(buttonStyle);
    this->bonusButton->setStyleSheet(buttonStyle);
    this->tableButton->setStyleSheet(buttonStyle);

}

GUI::~GUI() = default;

void GUI::chooseAdminFileType() {
    this->hide();

    // choose the file type
    adminFileWidget = new QWidget{};
    adminFileWidget->setMinimumSize(300, 100);
    auto *fileTypeLayout = new QVBoxLayout{adminFileWidget};
    adminFileWidget->setLayout(fileTypeLayout);

    QFont fileTypeFont("Arial", 15, QFont::Bold);

    /// --- file type label --- ///
    auto *fileTypeLabel = new QLabel{"Choose the file type:"};
    fileTypeLayout->addWidget(fileTypeLabel);

    fileTypeLabel->setFont(fileTypeFont);
    fileTypeLabel->setAlignment(Qt::AlignCenter);

    /// --- file type buttons --- ///
    auto *fileTypeButtonsLayout = new QHBoxLayout{};
    fileTypeLayout->addLayout(fileTypeButtonsLayout);

    auto *databaseButton = new QPushButton{"Database"};
    databaseButton->setFont(fileTypeFont);
    databaseButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; padding: 10px;");
    // ^ Set background color, text color, border, and padding

    auto *fileTextButton = new QPushButton{"Text file"};
    fileTextButton->setFont(fileTypeFont);
    fileTextButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");
    // ^ Set background color, text color, border, and padding

    fileTypeButtonsLayout->addWidget(databaseButton);
    fileTypeButtonsLayout->addWidget(fileTextButton);

    QObject::connect(databaseButton, &QPushButton::clicked, this, &GUI::setDatabaseFile);
    QObject::connect(fileTextButton, &QPushButton::clicked, this, &GUI::setTextFile);


    adminFileWidget->show();
}

void GUI::setDatabaseFile() {
    // set the file type to CSV
    this->adminService.setRepository(new DBRepository);

    // close the file type widget
    this->adminFileWidget->close();

    // start the user mode GUI
    this->AdminModeGUI();
}

void GUI::setTextFile() {
    // set the file type to HTML
    this->adminService.setRepository(new FileRepoShelterDogs);

    // close the file type widget
    this->adminFileWidget->close();

    // start the user mode GUI
    this->AdminModeGUI();
}

void GUI::AdminModeGUI() {
    this->adminWidget = new QWidget{};
    this->undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), adminWidget);


    this->redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), adminWidget);
    this->adminWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    this->adminWidget->setWindowIcon(QIcon(R"(C:\Users\User\CLionProjects\oop-a8-9-Eduardismund\project.png)"));
    this->adminWidget->show(); // show the admin window
    this->hide(); // hide the first page window
    this->adminWidget->setMinimumSize(600, 400);

    auto *bigLayout = new QVBoxLayout{this->adminWidget};

    /// --- title --- ///
    auto *adminLabel = new QLabel{"~ Admin mode ~"};
    QFont font("Arial", 20, QFont::Bold);
    adminLabel->setFont(font);
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setMinimumHeight(50);
    adminLabel->setStyleSheet("color: #333;"); // Set title color

    bigLayout->addWidget(adminLabel);

    // Layout for the admin page
    auto *adminLayout = new QHBoxLayout{};

    bigLayout->addLayout(adminLayout);

    /// --- left layout --- ///
    auto *leftLayout = new QVBoxLayout{};
    adminLayout->addLayout(leftLayout);

    /// --- title of list --- ///
    auto *dogsLabel = new QLabel{"Sheltered Dogs"};
    QFont font2("Arial", 15, QFont::Bold);
    dogsLabel->setFont(font2);
    dogsLabel->setAlignment(Qt::AlignCenter);
    dogsLabel->setMinimumHeight(20);
    dogsLabel->setStyleSheet("color: #666;"); // Set label color
    leftLayout->addWidget(dogsLabel);

    /// --- list dogs widget --- ///
    this->dogsListWidget = new QListWidget{};
    leftLayout->addWidget(this->dogsListWidget);
    QFont listFont("Arial", 12);
    this->dogsListWidget->setFont(listFont);
    this->dogsListWidget->setMinimumSize(200, 600);
    this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection); // select just one dog at a time
    this->populateListAdminMode();

    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, this, &GUI::showDogDataAdmin);

    /// --- right layout --- ///
    auto *rightLayout = new QVBoxLayout{};
    adminLayout->addLayout(rightLayout);

    /// --- form layout --- ///
    auto *formLayout = new QFormLayout{};
    rightLayout->addLayout(formLayout);

    QFont formFont("Arial", 15, QFont::Bold);

    /// form labels
    auto *nameLabel = new QLabel{"Name:"};
    nameLabel->setFont(formFont);
    nameLabel->setMinimumWidth(100);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("color: #333;"); // Set label color

    auto *breedLabel = new QLabel{"Breed:"};
    breedLabel->setFont(formFont);
    breedLabel->setMinimumWidth(100);
    breedLabel->setAlignment(Qt::AlignCenter);
    breedLabel->setStyleSheet("color: #333;"); // Set label color

    auto *ageLabel = new QLabel{"Age:"};
    ageLabel->setFont(formFont);
    ageLabel->setMinimumWidth(100);
    ageLabel->setAlignment(Qt::AlignCenter);
    ageLabel->setStyleSheet("color: #333;"); // Set label color

    auto *photoLabel = new QLabel{"Photo:"};
    photoLabel->setFont(formFont);
    photoLabel->setMinimumWidth(100);
    photoLabel->setAlignment(Qt::AlignCenter);
    photoLabel->setStyleSheet("color: #333;"); // Set label color

    /// form line edits
    this->nameLineEdit = new QLineEdit{};
    this->breedLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->photoLineEdit = new QLineEdit{};
    this->photoLineEdit->setMinimumWidth(300);

    formLayout->addRow(nameLabel, this->nameLineEdit);
    formLayout->addRow(breedLabel, this->breedLineEdit);
    formLayout->addRow(ageLabel, this->ageLineEdit);
    formLayout->addRow(photoLabel, this->photoLineEdit);

    /// --- buttons layout --- ///
    auto *buttonsLayout = new QVBoxLayout{};
    rightLayout->addLayout(buttonsLayout);

    QFont buttonsFont("Arial", 15, QFont::Bold);

    this->addDogButton = new QPushButton{"Add Dog"};
    this->addDogButton->setFont(buttonsFont);
    this->addDogButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; padding: 10px;");
    // ^ Set button background color, text color, border, and padding

    this->removeDogButton = new QPushButton{"Delete Dog"};
    this->removeDogButton->setFont(buttonsFont);
    this->removeDogButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");


    this->updateButton = new QPushButton{"Update Dog"};
    this->updateButton->setFont(buttonsFont);
    this->updateButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; padding: 10px;");


    this->saveAndExitButton = new QPushButton{"Save and Exit"};
    this->saveAndExitButton->setFont(buttonsFont);
    this->saveAndExitButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");

    this->undoButton= new QPushButton("Undo");
    this->undoButton->setFont(buttonsFont);
    this->undoButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; padding: 10px;");

    this->redoButton= new QPushButton("Redo");
    this->redoButton->setFont(buttonsFont);
    this->redoButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");

    // Create shortcuts for undo and redo

// Connect the shortcuts to the slots

    buttonsLayout->addWidget(this->addDogButton);
    buttonsLayout->addWidget(this->removeDogButton);
    buttonsLayout->addWidget(this->updateButton);
    buttonsLayout->addWidget(this->saveAndExitButton);
    buttonsLayout->addWidget(this->undoButton);
    buttonsLayout->addWidget(this->redoButton);

    QWidget *adminDisplayWindow = new QWidget();



//    adminDisplayWindow->setLayout(bigLayout);
//    adminDisplayWindow->show();



    QObject::connect(this->addDogButton, &QPushButton::clicked, this, &GUI::addDogGUI);
    QObject::connect(this->removeDogButton, &QPushButton::clicked, this, &GUI::deleteDogGUI);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateDogGUI);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitAdminGUI);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::executeUndo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::executeRedo);
    QObject::connect(undoShortcut, &QShortcut::activated, this, &GUI::executeUndo);
    QObject::connect(redoShortcut, &QShortcut::activated, this, &GUI::executeRedo);

//    this->undoShortcut->setContext(Qt::WidgetWithChildrenShortcut);
//    this->redoShortcut->setContext(Qt::WidgetWithChildrenShortcut);
}

void GUI::executeUndo() {
    try{
        this->adminService.undo();
    } catch(const std::exception& exception){
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::executeRedo() {
    try{
        this->adminService.redo();
    } catch(const std::exception& exception){
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}
void GUI::addDogGUI() {
    // take the data from the line edits and add the dog to the list
    std::string newName = this->nameLineEdit->text().toStdString();
    std::string newBreed = this->breedLineEdit->text().toStdString();
    int newAge = this->ageLineEdit->text().toInt();
    std::string newPhoto = this->photoLineEdit->text().toStdString();

    try {
        this->adminService.addDog(newBreed, newName, newPhoto, newAge);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::deleteDogGUI() {
    // take the nameDogToBeDeleted of the selected dog and delete it from the list
    std::string nameDogToBeDeleted = this->nameLineEdit->text().toStdString();

    try {
        this->adminService.deleteDog(nameDogToBeDeleted);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::updateDogGUI() {
    // take the data from the line edits and update the dog from the list
    std::string nameDogToBeUpdated = this->nameLineEdit->text().toStdString();
    std::string newBreed = this->breedLineEdit->text().toStdString();
    int newAge = this->ageLineEdit->text().toInt();
    std::string newPhoto = this->photoLineEdit->text().toStdString();

    try {
        this->adminService.updateDog(nameDogToBeUpdated, newBreed, newPhoto, newAge);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::saveAndExitAdminGUI() {
//    // save the dogs to the file and exit the admin mode

    this->adminWidget->close();
    this->show();
}

void GUI::saveAndExitBonusGUI() {
//    // save the dogs to the file and exit the admin mode
//    this->adminService.saveShelterDogToFile();
    this->bonusWidget->close();
    this->show();
}

void GUI::saveAndExitTableGUI() {
//    // save the dogs to the file and exit the admin mode
//    this->adminService.saveShelterDogToFile();
    this->tableWidget->close();
    this->show();
}

void GUI::populateListAdminMode() {
    // clear the list
    this->dogsListWidget->clear();

    // populate the list with the dogs from the repository
    for (const auto& dog : this->adminService.getDogs()) {
        this->dogsListWidget->addItem(QString::fromStdString(dog.getName() + " - " + dog.getBreed()));
    }
}

void GUI::showDogDataAdmin() {
    // Get the selected index
    int selectedIndex = this->dogsListWidget->currentIndex().row();

    // Check if the selected index is valid
    if (selectedIndex >= 0 && selectedIndex < this->adminService.getDogs().size()) {
        // Access the dog data based on the selected index
        std::vector<Dog> dogs = this->adminService.getDogs();
        this->dogList = this->adminService.getDogs();
        const auto& dog = dogs[selectedIndex];

        // Display the dog data in the line edits
        this->nameLineEdit->setText(QString::fromStdString(dog.getName()));
        this->breedLineEdit->setText(QString::fromStdString(dog.getBreed()));
        this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
        this->photoLineEdit->setText(QString::fromStdString(dog.getPhotograph()));
    }
}

///bonus mode

void GUI::bonusModeGUI() {
    this->bonusWidget = new QWidget{};
    this->bonusWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    this->bonusWidget->setWindowIcon(QIcon(R"(C:\Users\User\CLionProjects\oop-a8-9-Eduardismund\project.png)"));
    this->bonusWidget->show();
    this->hide();
    this->bonusWidget->setMinimumSize(800, 400);

    auto *bigLayout = new QVBoxLayout{this->bonusWidget};

    auto *topWidget = new QWidget{};
    auto *topLayout = new QVBoxLayout{topWidget};
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    auto *adminLabel = new QLabel{"~ Bonus mode ~"};
    QFont font("Arial", 16, QFont::Bold);
    adminLabel->setFont(font);
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setStyleSheet("color: #333;");
    topLayout->addWidget(adminLabel);
    bigLayout->addWidget(topWidget, 1);

    auto *bottomWidget = new QWidget{};
    auto *bottomLayout = new QVBoxLayout{bottomWidget};
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(0);

    auto *bonusLayout = new QVBoxLayout{};
    bottomLayout->addLayout(bonusLayout);

    auto *chartWidget = new ChartWidget{};
    bonusLayout->addWidget(chartWidget);

    this->adminService.setRepository(new DBRepository);
    std::vector<Dog> dogs = adminService.getDogs();
    chartWidget->setDogData(dogs);

    bigLayout->addWidget(bottomWidget, 3);
    QFont fontModes("Arial", 15, QFont::Bold);
    this->saveAndExitButton = new QPushButton{"Exit"};
    this->saveAndExitButton->setFont(fontModes);
    this->saveAndExitButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");

    bigLayout->addWidget(this->saveAndExitButton);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitBonusGUI);
}




void GUI::tableModeGUI() {
    // Create a new QWidget for the table view
    this->tableWidget = new QWidget{};
    this->tableWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter - Table View");
    this->tableWidget->setWindowIcon(QIcon(R"(C:\Users\User\CLionProjects\oop-a8-9-Eduardismund\project.png)"));
    this->tableWidget->show();
    this->hide();
    this->tableWidget->setMinimumSize(800, 400);


    QVBoxLayout *layout = new QVBoxLayout{tableWidget};
    auto *adminLabel = new QLabel{"~ Table view of the Adoption List ~"};
    QFont font("Arial", 16, QFont::Bold);
    adminLabel->setFont(font);
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setStyleSheet("color: #333;");
    layout->addWidget(adminLabel);


    this->serviceUser.setRepoAdopted(new RepoAdoptedDogsHTML);
    this->serviceUser.readAdoptedDogFromFile();
    auto *model = new AdoptionListModel{tableWidget};


    model->setAdoptionList(serviceUser.getDogsAdopted());


    QTableView *tableView = new QTableView{};
    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(tableView);

    tableWidget->show();


    QFont fontModes("Arial", 15, QFont::Bold);
    this->saveAndExitButton = new QPushButton{"Exit"};
    this->saveAndExitButton->setFont(fontModes);
    this->saveAndExitButton->setStyleSheet("background-color: #ff5733; color: white; border: none; padding: 10px;");

    layout->addWidget(this->saveAndExitButton);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitTableGUI);

}
