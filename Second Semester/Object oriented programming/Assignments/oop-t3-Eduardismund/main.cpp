#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    gui g(nullptr);
    g.show();
    return QApplication::exec();
}
