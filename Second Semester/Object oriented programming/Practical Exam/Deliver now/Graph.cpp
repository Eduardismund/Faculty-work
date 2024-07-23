#include "Graph.h"

Graph::Graph(Service& service, QWidget* parent)
        : QWidget{parent}, service{service}
{
    this->setFixedSize(800, 600);
    this->setWindowTitle("Map");
    service.attach(this);
}

Graph::~Graph()
{
    service.detach(this);
}

void Graph::update()
{
    this->repaint();
}

void Graph::paintEvent(QPaintEvent* event)
{
    (void)event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Set background to black
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());

    // Draw packages as white ellipses
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    for (const auto& package : service.getAllPackages())
    {
        if (package.getStatus())
            continue;

        auto loc = package.getLocation();
        painter.drawEllipse(loc.xCoordinate, loc.yCoordinate, 10, 10);
    }
}


void Graph::drawPackageInfo(QPainter& painter, const Package& package)
{
    QFont font("Arial", 8);
    painter.setFont(font);
    QFontMetrics fm(font);
    QString packageText = QString::fromStdString(package.toString());
    int textWidth = fm.horizontalAdvance(packageText);
    int textHeight = fm.height();

    auto loc = package.getLocation();
    int x = loc.xCoordinate;
    int y = loc.yCoordinate;

    painter.drawText(x + 15, y - 15, textWidth, textHeight, Qt::AlignLeft, packageText);
}