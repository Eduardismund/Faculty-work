#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_research.h"

class gui_research : public QMainWindow
{
    Q_OBJECT

public:
    gui_research(QWidget *parent = nullptr);
    ~gui_research();

private:
    Ui::gui_researchClass ui;
};
