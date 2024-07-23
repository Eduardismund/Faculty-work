#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include "Dog.h"
#include <QPainter>


class ChartWidget : public QWidget {
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void setDogData(const std::vector<Dog>& dogs);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<Dog> m_dogs;
};




class AdoptionListModel : public QAbstractTableModel {

public:
    AdoptionListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void setAdoptionList(const std::vector<Dog> &list);
private:
    std::vector<Dog> adoptionList;
};