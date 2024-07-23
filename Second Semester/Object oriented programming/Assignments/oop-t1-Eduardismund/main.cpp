#include "ui.h"
#include "tests.h"

int main() {
    tests t;
    t.TestAll();
    UI ui= UI();
    ui.run();
    return 0;
}