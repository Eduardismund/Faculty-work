//
// Created by User on 6/25/2024.
//

#ifndef DELIVER_NOW_COURIERWINDOW_H
#define DELIVER_NOW_COURIERWINDOW_H

#include <QWidget>

#include <QMainWindow>
#include <QListWidget>
#include "Service.h"
#include "Courier.h"
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class CourierWindow; }
QT_END_NAMESPACE

class CourierWindow : public QWidget, public Observer {
Q_OBJECT

public:
    explicit CourierWindow(Service& service, Courier& courier, QWidget* parent = nullptr);
    void populate();
    void fill();


    ~CourierWindow() override;

private:
    Service& service;
    Courier& courier;
    Ui::CourierWindow *ui;
    std::string selectedStreet;
    void update() override;
    QColor getRandomColor();
    void showWelcomeMessage();
    void shuffleStreets();

};


#endif //DELIVER_NOW_COURIERWINDOW_H
