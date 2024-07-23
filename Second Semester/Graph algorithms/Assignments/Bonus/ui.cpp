
#include <iostream>
#include <string>

#include "ui.h"
#include "service.h"
#include "exceptions.h"
#include <string.h>

UI::UI(Graph &graph): graph(graph),  newGraph(Graph()){}

void UI::ui_get_number_of_vertices() {
    int nr_vertices = this->graph.retrieve_vertex_count();
    std::cout << "\nThe number of vertices is: " << nr_vertices;
}

void UI::ui_get_number_of_edges() {
    int nr_edges = this->graph.retrieve_edges_count();
    std::cout << "\nThe number of edges is: " << nr_edges << "\n";
}

void UI::ui_copy_graph() {
    int command;
    std::cout << "Insert:\n\t1-if you want to restore an already copied Graph\n\t2-if you want to copy this graph:\n";
    std::cin >> command;
    if (command == 1) {
        if (this->newGraph.isEmpty()) {
            std::cout << "You have not made any copies.\n";
        } else {
            this->graph = this->newGraph; // Copy newGraph into graph
            std::cout << "You have restored the copied graph successfully.\n";
        }
    }
    if (command == 2) {
        this->newGraph = this->graph.copy_graph();
        std::cout << "Graph copied successfully!\n";
    }
}


void UI::run_app() {
    int cmd_as_int;
    std::string cmd, a;
    bool run_app = true;
    while (run_app) {
        UI::print_menu();
        std::cout << "\nPlease enter a command: ";
        std::getline(std::cin, cmd); // Read the entire line including Enter
        cmd_as_int = atoi(cmd.c_str());
        try {
            switch (cmd_as_int) {
                case 1:
                    this->ui_get_number_of_vertices();
                    this->ui_get_number_of_edges();
                    break;
                case 2:
                    this->ui_get_edges();
                    break;
                case 3:
                    this->ui_get_vertices();
                    break;
                case 4:
                    this->ui_get_cost_of_edge();
                    std::getline(std::cin, a);
                    break;
                case 5:
                    this->ui_in_degree_of_vertex();
                    std::getline(std::cin, a);
                    break;
                case 6:
                    std::cout<<"No ID's in this implementation";
                    break;
                case 7:
                    this->ui_check_edge();
                    break;
                case 8:
                    this->ui_change_edge_cost();
                    std::getline(std::cin, a);
                    break;
                case 9:
                    this->ui_add_edge();
                    std::getline(std::cin, a);
                    break;
                case 10:
                    this->ui_remove_edge();
                    std::getline(std::cin, a);
                    break;
                case 11:
                    this->ui_add_vertex();
                    std::getline(std::cin, a);
                    break;
                case 12:
                    this->ui_remove_vertex();
                    std::getline(std::cin, a);
                    break;
                case 13:
                    this->ui_copy_graph();
                    std::getline(std::cin, a);
                    break;
                case 14:
                    this->ui_read_graph_from_file();
                    break;
                case 15:
                    this->ui_write_graph_to_file();
                    break;
                case 16:
                    this->ui_generate_random_graph();
                    break;
                case 17:
                    this->ui_inbound_neighbours();
                    std::getline(std::cin, a);
                    break;
                case 18:
                    this->ui_outbound_neighbours();
                    std::getline(std::cin, a);
                    break;
                case 19:
                    run_app = false;
                    break;
                default:
                    std::cout << "\nInvalid command given.\n";
                    break;
            }
        }
        catch (GraphException& ge) {
            std::cout << ge.what();
            std::getline(std::cin, a);

        }
    }
}

void UI::ui_generate_random_graph(){
    std::string nr_vertices, nr_edges;
    int v, e;
    std::cout << "Give the number of vertices: ";
    std::getline(std::cin, nr_vertices);
    std::cout << "Give the number of edges: ";
    std::getline(std::cin, nr_edges);
    v=atoi(nr_vertices.c_str());
    e=atoi(nr_edges.c_str());
    try {
        this->graph = generate_random_graph(v, e);
    }
    catch (std::exception&) {
        std::cout << "\nError! Too many edges given!\n";
    }
}
void UI::ui_read_graph_from_file(){
    char file_name[256];
    std::cout << "\nPlease enter the filename (or press Enter to use the default): ";
    std::cin.getline(file_name, sizeof(file_name));

    // Check if the user entered nothing (just pressed Enter)
    if (file_name[0] == '\0') {
        // Use default filename or handle as needed
        std::cout << "Using default filename..." << std::endl;
    }

    std::cout << "Filename entered: " << file_name << std::endl;

    graph = read_graph_from_file(file_name);
    if (graph.isEmpty()) {
        std::cerr << "Error: Failed to read graph from file\n";
        return; // Exit function
    }

    std::cout << "Graph read successfully from file: " << file_name << std::endl;
}
void UI::print_menu() {
    std::cout << "\nMenu:\n"
                 "\t1. Retrieve the counts of vertices and edges\n"
                 "\t2. Retrieve the graph's edges\n"
                 "\t3. Retrieve the graph's vertices\n"
                 "\t4. Retrieve the cost of a specified edge\n"
                 "\t5. Retrieve the in-degree and out-degree of a specified vertex\n"
                 "\t6. Retrieve the endpoints of a specified edge\n"
                 "\t7. Determine if there is an edge from the first vertex to the second\n"
                 "\t8. Modify the cost of an edge\n"
                 "\t9. Add an edge\n"
                 "\t10. Remove an edge\n"
                 "\t11. Add a vertex\n"
                 "\t12. Remove a vertex\n"
                 "\t13. Copy the graph\n"
                 "\t14. Read graph from file\n"
                 "\t15. Write the graph to a file\n"
                 "\t16. Generate a random graph\n"
                 "\t17. Iterate through the set of inbound edges of a vertex\n"
                 "\t18. Iterate through the set of outbound edges of a vertex\n"
                 "\t19. Exit\n";
}

void UI::ui_get_vertices() {
    if (this->graph.retrieve_vertex_count() == 0) {
        std::cout << "\nThere are no vertices in the graph.\n";
        return;
    }
    std::pair<std::map<int, std::set<int>>::iterator, std::map<int, std::set<int>>::iterator> start_end_it;
    start_end_it = this->graph.out_relations();
    auto start_it = start_end_it.first;
    auto end_it = start_end_it.second;
    std::cout << "\nThese are the vertices from the graph: ";
    for (auto it = start_it; it != end_it; it++) {
        std::cout << it->first << " ";
    }
}

void UI::ui_get_edges() {
    if (this->graph.retrieve_edges_count() == 0) {
        std::cout << "\nThe graph has no edges.\n";
        return;
    }
    std::pair<std::map<std::pair<int, int>, int>::iterator, std::map<std::pair<int, int>, int>::iterator> start_end_it;
    start_end_it = this->graph.get_all_edges();
    auto start_it = start_end_it.first;
    auto end_it = start_end_it.second;
    std::cout << "\nThese are all the edges from the graph:\n";
    for (auto it = start_it; it != end_it; it++) {
        std::cout << it->first.first << "->" << it->first.second << ", cost of " << it->second << "\n";
    }
}


void UI::ui_check_edge() {
    int from, to;
    std::string a, b;
    std::cout << "\nGive the starting vertex of the graph: ";
    std::getline(std::cin, a);
    std::cout << "\nGive the ending vertex of the graph: ";
    std::getline(std::cin, b);
    from = atoi(a.c_str());
    to= atoi(b.c_str());
    if (this->graph.existence_edge(from, to)) {
        int cost = this->graph.retrieve_cost_of_edge(from, to);
        std::cout << "\nYes, the edge " << from << "->" << to << " is in the graph(cost of " << cost << ")\n";
    }else {
        std::cout << "\nNo, the edge " << from << "->" << to << " is NOT in the graph";
    }
}

void UI::ui_get_cost_of_edge() {
    int from, to;
    std::cout << "\nGive the starting vertex of the edge: ";
    std::cin >> from;
    std::cout << "\nGive the ending vertex of the edge: ";
    std::cin >> to;
    int cost = this->graph.retrieve_cost_of_edge(from, to);
    if(cost==-1)
        std::cout<<"\nError! The edge is not in the graph.\n";
    else
        std::cout << "\nThe cost of the edge " << from << " -> " << to << " is " << cost;
}

void UI::ui_in_degree_of_vertex() {
    int vertex;
    std::cout << "\nGive the vertex number: ";
    std::cin >> vertex;
    int in_degree = this->graph.get_in_degree(vertex);

    int out_degree = this->graph.get_out_degree(vertex);
    if(in_degree ==-1 and out_degree == -1)
        std::cout<<("\nError! The vertex is not in the graph.\n");
    else
    {
        std::cout << "\nThe in-degree of the vertex " << vertex << " is " << in_degree << "\n";
        std::cout << "\nThe out-degree of the vertex " << vertex << " is " << out_degree << "\n";
    }

}

void UI::ui_out_degree_of_vertex() {
    int vertex;
    std::cout << "\nGive the vertex number: ";
    std::cin >> vertex;
    int out_degree = this->graph.get_out_degree(vertex);
    std::cout << "\nThe out-degree of the vertex " << vertex << " is " << out_degree << "\n";
}

void UI::ui_outbound_neighbours() {
    int vertex;
    std::cout << "\nGive the vertex number: ";
    std::cin >> vertex;
    if (this->graph.get_out_degree(vertex) == 0) {
        std::cout << "\nThe vertex " << vertex << " has no outbound neighbours.\n";
        return;
    }
    std::pair<std::set<int>::iterator, std::set<int>::iterator> start_end_it;
    start_end_it = this->graph.get_outbound_neighbours(vertex);
    auto start_it = start_end_it.first;
    auto end_it = start_end_it.second;
    int neighbour, cost;
    std::cout << "\nThe outbound neighbours of vertex " << vertex << " are:\n";
    for (auto it = start_it; it != end_it; it++) {
        neighbour = *it;
        cost = this->graph.retrieve_cost_of_edge(vertex, neighbour);
        std::cout << "Start vertex: " <<vertex<< " ,End vertex: " <<neighbour << " ,Cost: " << cost << "\n";
    }
}

void UI::ui_inbound_neighbours() {
    int vertex;
    std::cout << "\nGive the vertex number: ";
    std::cin >> vertex;
    if (this->graph.get_in_degree(vertex) == 0) {
        std::cout << "\nThe vertex " << vertex << " has no inbound neighbours.\n";
        return;
    }
    std::pair<std::set<int>::iterator, std::set<int>::iterator> start_end_it;
    start_end_it = this->graph.get_inbound_neighbours(vertex);
    auto start_it = start_end_it.first;
    auto end_it = start_end_it.second;
    int neighbour, cost;
    std::cout << "\nThe inbound neighbours of vertex " << vertex << " are:\n";
    for (auto it = start_it; it != end_it; it++) {
        neighbour = *it;
        cost = this->graph.retrieve_cost_of_edge(neighbour, vertex);
        std::cout << "Start vertex: " <<neighbour<< " ,End vertex: " << vertex << " ,Cost: " << cost << "\n";
    }
}

void UI::ui_change_edge_cost() {
    int from, to, new_cost;
    std::cout << "\nGive the starting vertex of the edge: ";
    std::cin >> from;
    std::cout << "\nGive the ending vertex of the edge: ";
    std::cin >> to;
    std::cout << "\nGive the new cost of the edge: ";
    std::cin >> new_cost;
    this->graph.change_cost(from, to, new_cost);
    std::cout << "\nThe cost of the edge " << from << "->" << to << " was changed to " << new_cost << "\n";

}

void UI::ui_add_edge() {
    int from, to, cost;
    std::cout << "\nGive the starting vertex of the new edge: ";
    std::cin >> from;
    std::cout << "\nGive the ending vertex of the new edge: ";
    std::cin >> to;
    std::cout << "\nGive the cost of the new edge: ";
    std::cin >> cost;
    this->graph.add_edge(from, to, cost);
    std::cout << "\nThe edge " << from << "->" << to << "(cost of " << cost << ") was added to the graph.\n";
}

void UI::ui_remove_edge() {
    int from, to;
    std::cout << "\nGive the starting vertex of the edge: ";
    std::cin >> from;
    std::cout << "\nGive the ending vertex of the edge: ";
    std::cin >> to;
    this->graph.remove_edge(from, to);
    std::cout << "\nThe edge was removed.\n";
}

void UI::ui_add_vertex() {
    int vertex;
    std::cout << "\nGive the number of the new vertex: ";
    std::cin >> vertex;
    this->graph.add_vertex(vertex);
    std::cout << "\nThe vertex " << vertex << " was added to the graph.\n";
}

void UI::ui_remove_vertex() {
    int vertex;
    std::cout << "\nGive the number of the vertex: ";
    std::cin >> vertex;
    this->graph.remove_vertex(vertex);
    std::cout << "\nThe vertex " << vertex << " was removed from the graph.\n";
}

void UI::ui_write_graph_to_file() {
    char file_name[256];
    std::cout << "\nGive the name of the file (with extension): ";
    getchar();
    std::cin.getline(file_name, sizeof(file_name));
    write_graph_to_file(file_name, this->graph);
    std::cout << "\nThe graph was saved in " << file_name << "\n";
}