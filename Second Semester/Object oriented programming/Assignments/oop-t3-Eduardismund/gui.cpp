
#include <iostream>
#include "gui.h"
#include "ui_gui.h"


gui::gui(QWidget *parent) :
        QWidget(parent), ui(new Ui::gui) {
    ui->setupUi(this);
    s=service();
    populate();
    QObject::connect(this->ui->listOfEquations, &QListWidget::itemClicked, this, &gui::updateEq);
    QObject::connect(this->ui->solutionButton, &QPushButton::clicked, this, &gui::computeSol);
    QObject::connect(this->ui->updateLine, &QLineEdit::returnPressed, this, &gui::updateThe);
}

void gui::populate() {
    std::vector<Equation> eqs=s.getAllEqs();
    int n=0;
    for(const auto& e: eqs)
    {
        n++;
        QListWidgetItem* listItem= new QListWidgetItem(QString::fromStdString(std::to_string(n)+") "+e.toString()));

        this->ui->listOfEquations->addItem(listItem);
    }

}

void gui::computeSol() {
    std::string line=this->ui->selectEquation->text().toStdString();
    int a=line[0]-'0';
    std::vector<Equation> eqs=s.getAllEqs();
    Equation equation=Equation(0,0,0);
    for(Equation e: eqs)
    {
        if(a==1) {
            equation = e;
            break;
        }
        a--;
    }
    std::string sol=this->s.computeSol(equation);
    this->ui->solutionsLine->setText(QString::fromStdString(sol));

}
void gui::updateThe() {
    std::string line=this->ui->selectEquation->text().toStdString();
    std::string lineUP=this->ui->updateLine->text().toStdString();
    std::stringstream ss(lineUP);
    int aa,b,c;
    ss >> aa >> b >> c;
    int a=line[0]-'0';
    std::vector<Equation> eqs=s.getAllEqs();
    Equation equation=Equation(0,0,0);
    for(const auto& e: eqs)
    {

        if(a==1) {
            equation = e;
            break;
        }
        a--;
    }
    this->s.updateEq(equation.getA(), equation.getB(), equation.getC(), aa, b, c);

    this->ui->listOfEquations->clear();
    populate();

}
void gui::updateEq(QListWidgetItem *item) {
    this->ui->selectEquation->setText(item->text());
}

gui::~gui() {
    delete ui;
}
