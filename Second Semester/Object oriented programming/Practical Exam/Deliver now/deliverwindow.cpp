//
// Created by User on 6/25/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DeliverWindow.h" resolved

#include <QMessageBox>
#include "deliverwindow.h"
#include "ui_DeliverWindow.h"


DeliverWindow::DeliverWindow(Service& service, QWidget* parent) :
        QWidget(parent), ui(new Ui::DeliverWindow), service(service) {
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString("Deliver Company"));
    service.attach(this);
    for (const auto& person : service.getAllCouriers())
    {
        ui->comboBox->addItem(QString::fromStdString(person.getName()));
    }
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &DeliverWindow::add);

    populate();

}

void DeliverWindow::populate() {
    this->ui->listWidget->clear();
    std::vector<Package> all=this->service.getAllPackages();
    std::string st="";
    for(const auto& p: all)
    {
        if(p.getStatus()==false)
            st="- Not delivered";
        else
            st="- Delivered";
        std::string au=p.toString()+st;
        ui->listWidget->addItem(QString::fromStdString(au));
    }
}

void DeliverWindow::add() {
    QString courierName = ui->comboBox->currentText();
    if (courierName.isEmpty()) {
        return;
    }
    if (courierName == "")
    {
        QMessageBox::warning(this, "Warning", "Please select a courier!");
        return;
    }

    QString sender = ui->lineEdit->text();
    QString address = ui->lineEdit_2->text();
    QString xStr = ui->lineEdit_3->text();
    QString yStr = ui->lineEdit_4->text();

    if (sender.isEmpty() || address.isEmpty() || xStr.isEmpty() || yStr.isEmpty()) {
        return;
    }

    int x = xStr.toInt();
    int y = yStr.toInt();

    if (sender.isEmpty() || address.isEmpty()) {
        return;
    }

    // Create and add the new package to the service
    Location location(x, y); // Create a Location object

    // Create and add the new package to the service and the courier
    Package newPackage(sender.toStdString(), address.toStdString(), location, false); // Assuming false for not delivered status

    service.addPackage(newPackage);

    // Update the UI
    populate();
}

void DeliverWindow::update() {populate();}

DeliverWindow::~DeliverWindow() {
    delete ui;
}
