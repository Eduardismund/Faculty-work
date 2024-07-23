//
// Created by teodo on 6/19/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"
#include <QMessageBox>
#include <sstream>
#include <algorithm>
#include <QDebug>

GUI::GUI(Service &service, User user, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), serv(service), user(user) {
    ui->setupUi(this);

    QString windowTitle = QString::fromStdString(user.getName());
    this->setWindowTitle(windowTitle);
    serv.addObserver(this);

    this->populate();
    connect(this->ui->comboBox, &QComboBox::currentIndexChanged, this, &GUI::filter);
    connect(this->ui->pushButtonAdd, &QPushButton::clicked, this, &GUI::add);
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &GUI::showOffers);
    connect(this->ui->pushButton, &QPushButton::clicked, this, &GUI::bid);
}

GUI::~GUI() {
    if (ui) {
        delete ui;
    }
}

void GUI::populate() {

    this->putInComboBox();
    ui->listWidget->clear();

    for (auto item : serv.getItems()) {
        QString name = QString::fromStdString(item.getName());
        QString category = QString::fromStdString(item.getCategory());
        QString price = QString::number(item.getPrice());
        QString itemString = QString("%1,%2,%3").arg(name).arg(category).arg(price);
        ui->listWidget->addItem(itemString);
    }

    serv.notifyAllObservables();
}

void GUI::update() {

    this->ui->listWidget->clear();

    auto items = serv.getItems();
    if (category != "all") {
        items = serv.sortByCategory(category);
    }

    for (auto item : items) {
        QString name = QString::fromStdString(item.getName());
        QString category = QString::fromStdString(item.getCategory());
        QString price = QString::number(item.getPrice());
        QString itemString = QString("%1,%2,%3").arg(name).arg(category).arg(price);
        ui->listWidget->addItem(itemString);
    }
}

void GUI::filter() {
    QString nameQ = this->ui->lineEditName->text();
    QString categoryQ = this->ui->lineEditCategory->text();
    QString priceQ = this->ui->qLineEditPrice->text();
    category = ui->comboBox->currentText().toStdString();
    serv.notifyAllObservables();
}

void GUI::putInComboBox() {
    this->ui->comboBox->clear();
    std::vector<std::string> categories{"all"};
    this->ui->comboBox->addItem(QString::fromStdString("all"));

    for (auto item : serv.getItems()) {
        QString category = QString::fromStdString(item.getCategory());
        if (std::find(categories.begin(), categories.end(), item.getCategory()) == categories.end()) {
            categories.push_back(item.getCategory());
            ui->comboBox->addItem(category);
        }
    }

    serv.notifyAllObservables();
    QString nameQ = this->ui->lineEditName->text();
    QString categoryQ = this->ui->lineEditCategory->text();
    QString priceQ = this->ui->qLineEditPrice->text();
}

void GUI::add() {
    QString nameQ = this->ui->lineEditName->text();
    QString categoryQ = this->ui->lineEditCategory->text();
    QString priceQ = this->ui->qLineEditPrice->text();

    std::string name = nameQ.toStdString();
    std::string category = categoryQ.toStdString();
    int price = priceQ.toInt();

    if (name.empty() || category.empty() || price <= 0) {
        QMessageBox::warning(this, "Error", "Invalid data!");
    } else {
        Item item(name, category, price, {});

        if (item.getPrice() > 0) {
            serv.addItem(item);
            this->putInComboBox();
            this->update();
            this->serv.notifyAllObservables();
        }
    }
}


std::tuple<int, int, int> parseDate(const std::string& date) {
    std::stringstream ss(date);
    std::string day, month, year;
    std::getline(ss, day, '.');
    std::getline(ss, month, '.');
    std::getline(ss, year, '.');
    return std::make_tuple(std::stoi(year), std::stoi(month), std::stoi(day));
}

void GUI::showOffers() {
    auto currentItem = ui->listWidget->currentItem();
    if (!currentItem) return;

    QString currentItemText = currentItem->text();
    std::string itemDetails = currentItemText.toStdString();
    std::vector<std::string> tokens;
    char delim = ',';
    std::stringstream ss{itemDetails};
    std::string current;
    while (std::getline(ss, current, delim)) {
        tokens.push_back(current);
    }

    if (tokens.empty()) {
        QMessageBox::warning(this, "Error", "Invalid data!");
        return;
    }

    ui->listWidget_2->clear();
    for (auto item : serv.getItems()) {
        if (item.getName() == tokens[0]) {
            auto offerList = item.getList();
            std::sort(offerList.begin(), offerList.end(), [](const auto& a, const auto& b) {
                auto dateA = parseDate(std::get<1>(a));
                auto dateB = parseDate(std::get<1>(b));
                return dateA < dateB;
            });

            for (const auto& offer : offerList) {
                QString offerString = QString("User Id: %1, Date: %2, Offered sum: %3")
                        .arg(QString::number(std::get<0>(offer)))
                        .arg(QString::fromStdString(std::get<1>(offer)))
                        .arg(QString::number(std::get<2>(offer)));
                ui->listWidget_2->addItem(offerString);
            }
        }
    }
}

void GUI::bid() {


    if (user.getType() != "collector") {
        QMessageBox::warning(this, "Error!", "You are not a collector!");
        return;
    }

    QString bidAmount = this->ui->qLineEditBid->text();
    int offer = bidAmount.toInt();

    if (offer < 0) {
        QMessageBox::warning(this, "Error!", "Negative sum!");
    } else {
        auto *currentItem = this->ui->listWidget->currentItem();
        if (!currentItem) return;

        QString itemStringQ = currentItem->text();
        std::string itemString = itemStringQ.toStdString();
        char delim = ',';
        std::vector<std::string> tokens;
        std::stringstream ss{itemString};
        std::string current;
        while (std::getline(ss, current, delim)) {
            tokens.push_back(current);
        }


        for (auto &item : serv.getItems()) {
            if (item.getName() == tokens[0]) {
                if (offer > 0) {
                    item.setPrice(offer);
                    auto offerList = item.getList();
                    offerList.emplace_back(user.getId(), "27.06.2024", offer);
                    item.setList(offerList);
                    serv.notifyAllObservables();
                    this->update();
                } else {
                    QString priceDebug = "Offer is non-positive during bid";
                }
                break;
            }
        }
    }
}
