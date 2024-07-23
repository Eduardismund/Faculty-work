#include "GUI.h"


void GUI::chooseUserFileType() {
    this->hide();

    // choose the file type
    userFileWidget = new QWidget{};
    userFileWidget->setMinimumSize(300, 100);
    auto *fileTypeLayout = new QVBoxLayout{userFileWidget};
    userFileWidget->setLayout(fileTypeLayout);

    QFont fileTypeFont("Arial", 15, QFont::Bold);

    /// --- file type label --- ///
    auto *fileTypeLabel = new QLabel{"Choose the file type:"};
    fileTypeLayout->addWidget(fileTypeLabel);

    fileTypeLabel->setFont(fileTypeFont);
    fileTypeLabel->setAlignment(Qt::AlignCenter);

    /// --- file type buttons --- ///
    auto *fileTypeButtonsLayout = new QHBoxLayout{};
    fileTypeLayout->addLayout(fileTypeButtonsLayout);

    auto *csvButton = new QPushButton{"CSV"};
    csvButton->setFont(fileTypeFont);

    auto *htmlButton = new QPushButton{"HTML"};
    htmlButton->setFont(fileTypeFont);

    fileTypeButtonsLayout->addWidget(csvButton);
    fileTypeButtonsLayout->addWidget(htmlButton);

    QObject::connect(csvButton, &QPushButton::clicked, this, &GUI::setCSVFile);
    QObject::connect(htmlButton, &QPushButton::clicked, this, &GUI::setHTMLFile);

    userFileWidget->show();

}

void GUI::setCSVFile() {
    // set the file type to CSV
    this->serviceUser.setRepoAdopted(new RepoAdoptedDogsCSV);
    this->adminService.setRepository(new DBRepository);

    // close the file type widget
    this->userFileWidget->close();

    // start the user mode GUI
    this->UserModeGUI();
}

void GUI::setHTMLFile() {
    // set the file type to HTML
    this->serviceUser.setRepoAdopted(new RepoAdoptedDogsHTML);
    this->adminService.setRepository(new DBRepository);

    // close the file type widget
    this->userFileWidget->close();

    // start the user mode GUI
    this->UserModeGUI();
}

void GUI::UserModeGUI()
// it will be fragmented in 3 vertical parts:
// - the title  "~ User Mode ~"
// - the main part, where the user can see the dogs, and the buttons
// -- the main part will be fragmented in 2 horizontal parts:
// --- the left part, also fragmented in 2 horizontal parts:
// ---- the top part, where will be the title Sheltered Dogs
// ---- the bottom part, where will be the list of dogs from the shelter
// --- the right part, also fragmented in 3 horizontal parts:
// ---- the top part, where will be the title Current Dog
// ---- the middle part, where will be the dog's data, in a form layout like in the admin mode
// ---- the bottom part, where will be the buttons Show Photo, Adopt Dog, Next Dog, See Adopted List, Save and Exit
// - the bottom part will be fragmented in 2 vertical parts:
// -- the up part will be also fragmented in 2 horizontal parts:
// --- the left part will have the Breed form layout like in the admin mode
// --- the right part will have the Age form layout like in the admin mode
// -- the bottom part will have a button called Filter


/// the big widget containing all the other widgets
{
//        std::vector<Dog> dogs=this->serviceUser.getDogShelter();
    userWidget = new QWidget{};


    this->userWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    // this->userWidget->setWindowIcon(QIcon(R"(C:\Users\Admin\Documents\GitHub\a89-912-enache-vlad\animal-shelter.png)"));

    userWidget->show();


    userWidget->setMinimumSize(600, 600);
    auto *mainLayout = new QVBoxLayout{userWidget};
    userWidget->setLayout(mainLayout);

    /// the title
    {
        auto *titleLabel = new QLabel{"~ User Mode ~"};
        QFont titleFont("Arial", 20, QFont::Bold);
        titleLabel->setFont(titleFont);
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);
    }


    {
        auto *mainPartWidget = new QWidget{};
        auto *mainPartLayout = new QHBoxLayout{mainPartWidget};
        mainPartWidget->setLayout(mainPartLayout);
        mainLayout->addWidget(mainPartWidget);

        /// the left part
        {

            auto *leftPartWidget = new QWidget{};
            auto *leftPartLayout = new QVBoxLayout{leftPartWidget};
            leftPartWidget->setLayout(leftPartLayout);
            mainPartLayout->addWidget(leftPartWidget);

            /// the top part of the left part
            auto *leftTopPartWidget = new QWidget{};
            auto *leftTopPartLayout = new QHBoxLayout{leftTopPartWidget};
            leftTopPartWidget->setLayout(leftTopPartLayout);
            leftPartLayout->addWidget(leftTopPartWidget);

            /// the title Sheltered Dogs
            auto *shelteredDogsLabel = new QLabel{"Sheltered Dogs:"};
            QFont shelteredDogsFont("Arial", 15, QFont::Bold);
            shelteredDogsLabel->setFont(shelteredDogsFont);
            leftTopPartLayout->addWidget(shelteredDogsLabel);

            /// the bottom part of the left part
            auto *leftBottomPartWidget = new QWidget{};
            auto *leftBottomPartLayout = new QHBoxLayout{leftBottomPartWidget};
            leftBottomPartWidget->setLayout(leftBottomPartLayout);
            leftPartLayout->addWidget(leftBottomPartWidget);

            /// the list of dogs from the shelter
            this->dogsListWidget = new QListWidget{};
            leftBottomPartLayout->addWidget(this->dogsListWidget);

            this->dogList = this->serviceUser.getDogShelter();
            populateListUserMode();
            this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            std::vector<Dog> dogs=this->serviceUser.getDogShelter();
            int i;
            for(auto dog: dogs)
                i++;
            int size = dogs.size();
            this->dogsListWidget->setCurrentRow(size - 1);
            // TODO: I have to find why I can not show the data first time
//                showDogDataUser();

            QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, this, &GUI::showDogDataUser);
        }

        /// the right part
        {
            auto *rightPartWidget = new QWidget{};
            auto *rightPartLayout = new QVBoxLayout{rightPartWidget};
            rightPartWidget->setLayout(rightPartLayout);
            mainPartLayout->addWidget(rightPartWidget);

            /// the top part of the right part
            auto *rightTopPartWidget = new QWidget{};
            auto *rightTopPartLayout = new QHBoxLayout{rightTopPartWidget};
            rightTopPartWidget->setLayout(rightTopPartLayout);
            rightPartLayout->addWidget(rightTopPartWidget);

            /// the title Current Dog
            auto *currentDogLabel = new QLabel{"Current Dog:"};
            QFont currentDogFont("Arial", 15, QFont::Bold);
            currentDogLabel->setFont(currentDogFont);
            rightTopPartLayout->addWidget(currentDogLabel);

            /// the middle part of the right part
            {
                auto *rightMiddlePartWidget = new QWidget{};
                auto *rightMiddlePartLayout = new QFormLayout{rightMiddlePartWidget};
                rightMiddlePartWidget->setLayout(rightMiddlePartLayout);
                rightPartLayout->addWidget(rightMiddlePartWidget);

                /// the form line info
                {
                    this->nameLabelInfo = new QLabel{};
                    this->nameLabelInfo->setAlignment(Qt::AlignCenter);
                    this->nameLabelInfo->setMinimumWidth(100);
                    this->nameLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                    this->breedLabelInfo = new QLabel{};
                    this->breedLabelInfo->setAlignment(Qt::AlignCenter);
                    this->breedLabelInfo->setMinimumWidth(100);
                    this->breedLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                    this->ageLabelInfo = new QLabel{};
                    this->ageLabelInfo->setAlignment(Qt::AlignCenter);
                    this->ageLabelInfo->setMinimumWidth(100);
                    this->ageLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                    this->photoLabelInfo = new QLabel{};
                    this->photoLabelInfo->setAlignment(Qt::AlignCenter);
                    this->photoLabelInfo->setMinimumWidth(300);
                    this->photoLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                }

                /// form labels
                {
                    QFont formFont("Arial", 15, QFont::Bold);

                    auto *nameLabel = new QLabel{"Name:"};
                    nameLabel->setFont(formFont);
                    nameLabel->setMinimumWidth(100);
                    nameLabel->setAlignment(Qt::AlignCenter);

                    auto *breedLabel = new QLabel{"Breed:"};
                    breedLabel->setFont(formFont);
                    breedLabel->setMinimumWidth(100);
                    breedLabel->setAlignment(Qt::AlignCenter);

                    auto *ageLabel = new QLabel{"Age:"};
                    ageLabel->setFont(formFont);
                    ageLabel->setMinimumWidth(100);
                    ageLabel->setAlignment(Qt::AlignCenter);

                    /// adding the form labels and info to the form layout
                    {
                        rightMiddlePartLayout->addRow(nameLabel, nameLabelInfo);
                        rightMiddlePartLayout->addRow(breedLabel, breedLabelInfo);
                        rightMiddlePartLayout->addRow(ageLabel, ageLabelInfo);
                    }
                }
            }

            /// the bottom part of the right part
            {
                auto *rightBottomPartWidget = new QWidget{};
                auto *rightBottomPartLayout = new QVBoxLayout{rightBottomPartWidget};
                rightBottomPartWidget->setLayout(rightBottomPartLayout);
                rightPartLayout->addWidget(rightBottomPartWidget);

                /// the buttons
                {
                    /// show photo button
                    {
                        this->showPhotoButton = new QPushButton{"Show Photo"};
                        rightBottomPartLayout->addWidget(this->showPhotoButton);
                        QObject::connect(this->showPhotoButton, &QPushButton::clicked, this, &GUI::showPhoto);
                    }

                    /// the adopt dog button
                    {
                        this->adoptDogButton = new QPushButton{"Adopt Dog"};
                        rightBottomPartLayout->addWidget(this->adoptDogButton);
                        QObject::connect(this->adoptDogButton, &QPushButton::clicked, this, &GUI::adoptDogGUI);
                    }

                    /// the Next Dog button
                    {
                        this->nextDogButton = new QPushButton{"Next Dog"};
                        rightBottomPartLayout->addWidget(this->nextDogButton);
                        QObject::connect(this->nextDogButton, &QPushButton::clicked, this, &GUI::nextDogGUI);
                    }

                    /// See Adoption List button
                    {
                        this->seeAdoptedDogsButton = new QPushButton{"See Adoption List"};
                        rightBottomPartLayout->addWidget(this->seeAdoptedDogsButton);
                        QObject::connect(this->seeAdoptedDogsButton, &QPushButton::clicked, this, &GUI::seeAdoptedDogsGUI);
                    }

                    /// the Save and Exit button
                    {
                        this->saveAndExitUserButton = new QPushButton{"Save and Exit"};
                        rightBottomPartLayout->addWidget(this->saveAndExitUserButton);
                        QObject::connect(this->saveAndExitUserButton, &QPushButton::clicked, this, &GUI::saveAndExitUserGUI);
                    }
                }
            }
        }
    }

    /// the bottom part -
    {
        auto *bottomPartWidget = new QWidget{};
        auto *bottomPartLayout = new QVBoxLayout{bottomPartWidget};
        bottomPartWidget->setLayout(bottomPartLayout);
        mainLayout->addWidget(bottomPartWidget);

        /// the up part
        {
            auto *bottomUpPartWidget = new QWidget{};
            auto *bottomUpPartLayout = new QHBoxLayout{bottomUpPartWidget};
            bottomUpPartWidget->setLayout(bottomUpPartLayout);
            bottomPartLayout->addWidget(bottomUpPartWidget);


            /// the breed filter
            {
                auto *breedFilterWidget = new QWidget{};
                auto *breedFilterLayout = new QVBoxLayout{breedFilterWidget};
                breedFilterWidget->setLayout(breedFilterLayout);
                bottomUpPartLayout->addWidget(breedFilterWidget);

                /// the breed filter label
                {
                    auto *breedFilterLabel = new QLabel{"Breed:"};
                    QFont breedFilterFont("Arial", 10, QFont::Bold);
                    breedFilterLabel->setFont(breedFilterFont);
                    breedFilterLayout->addWidget(breedFilterLabel);
                }

                /// the breed filter line
                {
                    this->breedLineEdit = new QLineEdit{};
                    breedFilterLayout->addWidget(this->breedLineEdit);
                }
            }

            /// the age filter
            {
                auto *ageFilterWidget = new QWidget{};
                auto *ageFilterLayout = new QVBoxLayout{ageFilterWidget};
                ageFilterWidget->setLayout(ageFilterLayout);
                bottomUpPartLayout->addWidget(ageFilterWidget);

                /// the age filter label
                {
                    auto *ageFilterLabel = new QLabel{"Age:"};
                    QFont ageFilterFont("Arial", 10, QFont::Bold);
                    ageFilterLabel->setFont(ageFilterFont);
                    ageFilterLayout->addWidget(ageFilterLabel);
                }

                /// the age filter line
                {
                    this->ageLineEdit = new QLineEdit{};
                    ageFilterLayout->addWidget(this->ageLineEdit);
                }
            }

        }

        /// the down part
        {
            auto *bottomDownPartWidget = new QWidget{};
            auto *bottomDownPartLayout = new QHBoxLayout{bottomDownPartWidget};
            bottomDownPartWidget->setLayout(bottomDownPartLayout);
            bottomPartLayout->addWidget(bottomDownPartWidget);

            /// the filter button
            {
                this->seeFilteredDogsButton = new QPushButton{"Filter"};
                bottomDownPartLayout->addWidget(this->seeFilteredDogsButton);
                QObject::connect(this->seeFilteredDogsButton, &QPushButton::clicked, this, &GUI::filterDogsGUI);
            }
        }
    }
}


void GUI::populateListUserMode() {
    // clear the list
    this->dogsListWidget->clear();

    // get the list of dogs from the shelter
    auto dogs = this->dogList;

    if(dogs.empty()){
        QString emptyString = "No dogs left in the shelter!";
        auto *emptyItem = new QListWidgetItem{emptyString};
        this->dogsListWidget->addItem(emptyItem);
    }

    // add the dogs to the list
    for (auto &dog : dogs) {
        QString dogString = QString::fromStdString(dog.getName() + " - " + dog.getBreed());
        auto *dogItem = new QListWidgetItem{dogString};
        this->dogsListWidget->addItem(dogItem);
    }

}

void GUI::showDogDataUser() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    // get the name of the dog from the list

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto nameAndBreed = selectedIndexes.at(0).data().toString().toStdString();
    auto name = nameAndBreed.substr(0, nameAndBreed.find(" - "));

    auto dog = this->adminService.getDogByName(name);

    // set the text of the lineEdits with the dog data
    this->nameLabelInfo->setText(QString::fromStdString(dog.getName()));
    this->breedLabelInfo->setText(QString::fromStdString(dog.getBreed()));
    this->ageLabelInfo->setText(QString::number(dog.getAge()));
    this->photoLabelInfo->setText(QString::fromStdString(dog.getPhotograph()));



}

void GUI::showPhoto() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto dogs = this->serviceUser.getDogShelter();
    if (selectedIndex >= dogs.size())
        return;
    auto dog = dogs[selectedIndex];

    // open the photo in a browser
    QString link = QString::fromStdString(dog.getPhotograph());
    QDesktopServices::openUrl(QUrl(link));

}

void GUI::nextDogGUI() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto dogs = this->dogList;
    if (selectedIndex >= dogs.size())
        return;
    auto dog = dogs[selectedIndex];

    // set the text of the lineEdits with the dog data
    this->nameLabelInfo->setText(QString::fromStdString(dog.getName()));
    this->breedLabelInfo->setText(QString::fromStdString(dog.getBreed()));
    this->ageLabelInfo->setText(QString::number(dog.getAge()));
    this->photoLabelInfo->setText(QString::fromStdString(dog.getPhotograph()));

    // select the next dog in the list
    if (selectedIndex == dogs.size() - 1)
        selectedIndex = 0;
    else
        selectedIndex++;
    this->dogsListWidget->setCurrentRow(selectedIndex);


}

void GUI::adoptDogGUI() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto nameAndBreed = selectedIndexes.at(0).data().toString().toStdString();
    auto name = nameAndBreed.substr(0, nameAndBreed.find(" - "));

//    cout << name << endl;
    auto dog = this->adminService.getDogByName(name);


    /// if here we are not in the filtered list
    if(this->dogList == this->serviceUser.getDogShelter()) {
        // adopt the dog
        try {
            this->serviceUser.adoptDog(dog.getName());
        }
        catch (std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
        // update the list
        this->dogList = this->serviceUser.getDogShelter();


    }
    else{
        // adopt the dog
        try {
            this->serviceUser.adoptDog(dog.getName());
        }
        catch (std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }

        // open again filtered list
        this->filterDogsGUI();
    }

    this->populateListUserMode();

    // set the index to the next dog
    if (selectedIndex == this->dogList.size())
        selectedIndex = 0;
    this->dogsListWidget->setCurrentRow(selectedIndex);

    // clear the lineEdits
    this->nameLabelInfo->clear();
    this->breedLabelInfo->clear();
    this->ageLabelInfo->clear();
    this->photoLabelInfo->clear();

}

void GUI::seeAdoptedDogsGUI() {
    // open the file with the adopted dogs
    this->serviceUser.getRepoAdopted()->write();
    this->serviceUser.getRepoAdopted()->display();
}

void GUI::saveAndExitUserGUI() {
    // save the adoption list
//    this->serviceUser.saveShelterDogToFile();

//    // save the shelter list
//    this->serviceUser.saveAdoptedDogToFile();

    // exit the user mode
    this->userWidget->close();
//    this->userWidget = nullptr;
    this->show();
}

void GUI::filterDogsGUI() {
    // get the breed and age
    QString breed = this->breedLineEdit->text();
    QString age = this->ageLineEdit->text();

    if (breed.isEmpty() || age.isEmpty()) {
        /// if the breed or age are empty, show all the dogs
        this->dogList = this->serviceUser.getDogShelter();
        int size = this->serviceUser.getDogShelter().size();
        this->dogsListWidget->setCurrentRow(0);
        populateListUserMode();

    }
    else {
        // convert the age to int
        int ageInt = age.toInt();

        // filter the dogs
        auto filteredDogs = this->serviceUser.getDogsFiltered(breed.toStdString(), ageInt);

        /// change the dogList to the filtered dogs
        this->dogList = filteredDogs;

        // populate the list with the filtered dogs
        this->dogsListWidget->clear();

        if (filteredDogs.empty()) {
            // if there are no more filtered dogs, come back to all dogs
            this->dogList = this->serviceUser.getDogShelter();
        }
        else {
            for (auto &dog: filteredDogs) {
                QString dogString = QString::fromStdString(dog.getName() + " - " + dog.getBreed());
                auto *dogItem = new QListWidgetItem{dogString};
                this->dogsListWidget->addItem(dogItem);
            }


            this->dogsListWidget->setCurrentRow(0);
        }
    }
}

