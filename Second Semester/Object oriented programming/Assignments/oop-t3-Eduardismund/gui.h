
// Created by User on 5/27/2024.
#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget {
    Q_OBJECT

public:
    explicit gui(QWidget *parent = nullptr);
    void populate();
    void computeSol();
    void updateEq(QListWidgetItem *item);
    void updateThe();
    ~gui() override;

private:
    Ui::gui *ui;
    service s;
};