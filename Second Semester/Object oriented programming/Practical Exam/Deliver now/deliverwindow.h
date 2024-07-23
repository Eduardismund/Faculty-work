//
// Created by User on 6/25/2024.
//

#ifndef DELIVER_NOW_DELIVERWINDOW_H
#define DELIVER_NOW_DELIVERWINDOW_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "Service.h"
#include "Courier.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DeliverWindow; }
QT_END_NAMESPACE

class DeliverWindow : public QWidget, Observer {
Q_OBJECT

public:
    explicit DeliverWindow(Service& service,QWidget *parent = nullptr);
    void populate();
    void update() override;
    void add();


    ~DeliverWindow() override;

private:
    Ui::DeliverWindow *ui;
    Service& service;
};


#endif //DELIVER_NOW_DELIVERWINDOW_H
