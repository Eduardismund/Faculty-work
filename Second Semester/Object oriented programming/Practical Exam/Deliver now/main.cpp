#include "courierwindow.h"
#include "Courier.h"
#include "Service.h"
#include "Graph.h"
#include <QtWidgets/QApplication>
#include <ranges>
#include <algorithm>
#include "deliverwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    CourierRepository courierRepository;
    Service service{ courierRepository };
    std::vector<Package> packages = service.getAllPackages();
    auto couriers = service.getAllCouriers();

    if (couriers.empty()) {
        // Handle case when there are no couriers available
        return 0;
    }

    DeliverWindow d{ service };
    d.show();

    Graph graph{ service };
    graph.show();

    // Make a copy of the packages vector
    std::vector<Package> packagesCopy = packages;

    for (auto && courier : couriers)
    {
        auto* courierView = new CourierWindow(service, courier);

        courierView->setWindowTitle(QString::fromStdString(courier.getName()));
        courierView->show();
    }

    return a.exec();
}
