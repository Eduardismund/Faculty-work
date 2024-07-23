#include "TabelList.h"

AdoptionListModel::AdoptionListModel(QObject *parent)
        : QAbstractTableModel(parent) {}

int AdoptionListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return adoptionList.size();
}

int AdoptionListModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant AdoptionListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= adoptionList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Dog &dog = adoptionList.at(index.row());
        switch (index.column()) {
            case 0: return QVariant(QString::fromStdString(dog.getName()));
            case 1: return QVariant(QString::fromStdString(dog.getBreed()));
            case 2: return QVariant(dog.getAge());
            case 3: return QVariant(QString::fromStdString(dog.getPhotograph()));
            default: return QVariant();
        }
    }
    return QVariant();
}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QVariant("Name");
            case 1: return QVariant("Breed");
            case 2: return QVariant("Age");
            case 3: return QVariant("Photograph");
            default: return QVariant();
        }
    }
    return QVariant();
}

void AdoptionListModel::setAdoptionList(const std::vector<Dog> &list) {
    beginResetModel();
    adoptionList = list;
    endResetModel();
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


