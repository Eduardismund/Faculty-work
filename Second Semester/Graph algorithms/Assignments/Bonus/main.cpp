#include <iostream>
#include "Graph.h"
#include "service.h"
#include "ui.h"

int main() {
    Graph graph;
    UI ui = UI(graph);
    ui.run_app();
    std::cout << "\nHave a great day!\n";

    return 0;
}