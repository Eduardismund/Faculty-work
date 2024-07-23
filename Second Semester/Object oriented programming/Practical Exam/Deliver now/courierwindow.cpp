#include <QRandomGenerator>
#include <QMessageBox>
#include "courierwindow.h"
#include "ui_CourierWindow.h"

CourierWindow::CourierWindow(Service& service, Courier& courier, QWidget* parent) :
        QWidget(parent), ui(new Ui::CourierWindow), service(service), courier(courier)
{

    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(courier.getName()));
    service.attach(this);



    QString zoneInfo = "Zone: Center(" + QString::number(courier.getZone().c) + "), Radius(" + QString::number(courier.getZone().r) + ")";
    ui->lineEdit->setText(zoneInfo);
    selectedStreet = "All";
    ui->comboBox->addItem(QString("All"));
    for (const auto& street : courier.getStreets())
    {
        ui->comboBox->addItem(QString::fromStdString(street));
    }

    // Connect the comboBox signal to fill() slot
    QObject::connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]() { fill(); });

    // Connect the deliver button signal to delivery action
    QObject::connect(ui->pushButton, &QPushButton::clicked, [&, this]() {
        QListWidgetItem* item = ui->listWidget->currentItem();
        if (item == nullptr)
        {
            return;
        }

        std::string packageInfo = item->text().toStdString();
        int spaceIndex = packageInfo.find(" - ");
        std::string packageSender = packageInfo.substr(0, spaceIndex);
        std::string packageAddress = packageInfo.substr(spaceIndex + 3, packageInfo.size());
        service.deliverPackage(packageSender, packageAddress);
        QString zoneInfo = "Zone: Center(" + QString::number(courier.getZone().c) + "), Radius(" + QString::number(courier.getZone().r) + ")";
        ui->lineEdit->setText(zoneInfo);

    });

    // Populate the initial list of packages

    populate();
}

void CourierWindow::fill() {
    selectedStreet = ui->comboBox->currentText().toStdString();
    populate();
}

void CourierWindow::populate() {
    ui->listWidget->clear();
    std::vector<Package> courierPackages;
    for (const auto& package : service.getAllPackages())
    {
        bool isInStreets = std::ranges::find(courier.getStreets(), package.getAddress()) != courier.getStreets().end();
        bool isInZone = courier.isWithinZone(package.getLocation());

        if (!package.getStatus() && (isInStreets || isInZone) && (selectedStreet == "All" || selectedStreet == package.getAddress()))
        {
            courierPackages.push_back(package);
        }
    }

    for (const auto& package : courierPackages)
    {
        ui->listWidget->addItem(QString::fromStdString(package.toString()));
    }
}

void CourierWindow::update() {
    // Update the package list
    populate();

    // Notify the service to inform other couriers
}

CourierWindow::~CourierWindow() {
    service.detach(this);
    delete ui;
}

QColor CourierWindow::getRandomColor() {
    int red = QRandomGenerator::global()->bounded(256);
    int green = QRandomGenerator::global()->bounded(256);
    int blue = QRandomGenerator::global()->bounded(256);
    return QColor(red, green, blue);
}

void CourierWindow::shuffleStreets() {
    std::vector<std::string> streets = courier.getStreets();
    std::shuffle(streets.begin(), streets.end(), std::default_random_engine(QRandomGenerator::global()->generate()));
    for (const auto& street : streets) {
        qDebug() << QString::fromStdString(street);
    }
}

void CourierWindow::showWelcomeMessage() {
    QMessageBox::information(this, "Welcome", "Welcome, " + QString::fromStdString(courier.getName()) + "!");
}