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

    buttonsLayout->addWidget(this->adminModeButton);
    buttonsLayout->addWidget(this->userModeButton);
    buttonsLayout->addWidget(this->bonusButton);
    // add the buttons layout to the main layout
    firstPageLayout->addLayout(buttonsLayout);

    // connect the signals and slots
    QObject::connect(this->adminModeButton, &QPushButton::clicked, this, &GUI::chooseAdminFileType);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::chooseUserFileType);
    QObject::connect(this->bonusButton, &QPushButton::clicked, this, &GUI::bonusModeGUI);
    this->applyStyles();

}

void GUI::applyStyles() {

    this->setStyleSheet("background-color: #f0f0f0;");


    QString buttonStyle = "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
                          "QPushButton:hover { background-color: #45a049; }";
    this->adminModeButton->setStyleSheet(buttonStyle);
    this->userModeButton->setStyleSheet(buttonStyle);
    this->bonusButton->setStyleSheet(buttonStyle);

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


    buttonsLayout->addWidget(this->addDogButton);
    buttonsLayout->addWidget(this->removeDogButton);
    buttonsLayout->addWidget(this->updateButton);
    buttonsLayout->addWidget(this->saveAndExitButton);

    QObject::connect(this->addDogButton, &QPushButton::clicked, this, &GUI::addDogGUI);
    QObject::connect(this->removeDogButton, &QPushButton::clicked, this, &GUI::deleteDogGUI);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateDogGUI);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitAdminGUI);
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
    } else {
        // Handle invalid index (optional)
        qDebug() << "Invalid index or no dog selected.";
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

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent) {}

void ChartWidget::setDogData(const std::vector<Dog>& dogs) {
    m_dogs = dogs;
    update();
}

void ChartWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int margin = 50;
    int barWidth = (width() - 2 * margin) / 10;
    int maxHeight = height() - 2 * margin;

    std::vector<int> ageCounts(12, 0);
    for (const auto& dog : m_dogs) {
        int ageGroup = dog.getAge();
        ageCounts[ageGroup]++;
    }
    int maximum = *std::max_element(ageCounts.begin(), ageCounts.end());

    int maxData = *std::max_element(ageCounts.begin(), ageCounts.end());
    int maxBarHeight = maxHeight * maxData / maxData;
    maxBarHeight *= 3;
    double scaleFactor = static_cast<double>(maxHeight) / maxBarHeight;

    QFontMetrics fm(painter.font());
    for (int i = 0; i < ageCounts.size(); ++i) {
        int barHeight = maxHeight * ageCounts[i] / maxData;
        QColor barColor = QColor::fromHsv(i * 30, 255, 200);
        painter.setBrush(barColor);
        painter.drawRect(margin + i * barWidth, height() - margin - barHeight, barWidth, barHeight);
        if (ageCounts[i] != 0) {
            std::string name;
            int j = 1;
            for (const auto& dog : m_dogs) {
                if (dog.getAge() == i) {
                    name = dog.getName();
                    QString nameLabel = QString::fromStdString(name);
                    painter.setFont(QFont("Arial", 10, QFont::Bold));
                    painter.drawText(margin + i * barWidth + 7, height() - margin - barHeight + j * 17, nameLabel);
                    j++;
                }
            }
        }
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        QString ageLabel = QString::number(i);
        int textWidth = fm.horizontalAdvance(ageLabel);
        painter.drawText(margin + i * barWidth + barWidth / 2 - textWidth / 2,
                         height() - margin / 2 + fm.height() / 2 - 20, ageLabel);
    }

    painter.setPen(Qt::black);
    painter.drawLine(margin, height() - margin, width() - margin, height() - margin);
    painter.drawLine(margin, height() - margin, margin, margin - scaleFactor * maxBarHeight);

    int pointSize = 8;
    QPen pen = painter.pen();
    pen.setWidth(pointSize);
    painter.setPen(pen);
    for (int i = 0; i <= maximum; i++) {
        int barHeight = maxHeight * i / maxData;
        painter.drawPoint(margin, height() - margin - barHeight);
        QString ageLabel = QString::fromStdString(std::to_string(i));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(margin - 20, height() - margin - barHeight + 7, ageLabel);
    }

    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(width() / 2, height() - margin + 35, "Age Groups");

    painter.rotate(-90);
    painter.drawText(-height() / 2, margin / 2, "Number of Dogs");

    QFont titleFont("Arial", 14, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(width() / 2 - 50, margin / 2, 100, 50, Qt::AlignCenter, "Dog Age Distribution");
}
