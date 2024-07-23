
#include "service.h"
#include "exceptions.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

Graph read_graph_from_file(char *file_name){
    std::ifstream fin(file_name);
    if (!fin) {
        throw GraphException("Error: Unable to open file ");
        return Graph(0); // Return an empty graph
    }

    std::string current_line;
    int nr_vertices, nr_edges, _from, _to, _cost;

    // Read number of vertices and edges from the first line
    if (!getline(fin, current_line)) {
        throw GraphException("\nError: Unable to read number of vertices and edges.\n");
        fin.close();
        return Graph(0); // Return an empty graph
    }

    std::istringstream line_stream(current_line);
    if (!(line_stream >> nr_vertices >> nr_edges)) {
        throw GraphException("\nError: Unable to parse number of vertices and edges.\n");

    }
    Graph graph(nr_vertices);
    // Process each line in the file
    while (getline(fin, current_line)) {
        std::istringstream line_stream(current_line);

        // If there are two integers in the line, it represents an edge
        if (line_stream >> _from >> _to >> _cost) {
            if (!graph.is_vertex_in_graph(_from)) graph.add_vertex(_from);
            if (!graph.is_vertex_in_graph(_to)) graph.add_vertex(_to);
            graph.add_edge(_from, _to, _cost);
        } else {
            throw GraphException("\nError: Error: Unable to parse edge information.\n");
        }
    }

    fin.close();
    return graph;
}
void write_graph_to_file(char *file_name, Graph &graph) {
    int current_vertex, neighbour, cost;
    std::ofstream fout(file_name);

    std::pair<std::map<int, std::set<int>>::iterator, std::map<int, std::set<int>>::iterator> start_end_it;
    start_end_it = graph.out_relations();
    auto start_it = start_end_it.first;
    auto end_it = start_end_it.second;
    std::string graph_str;
    graph_str += std::to_string(graph.retrieve_vertex_count()) + " " + std::to_string(graph.retrieve_edges_count()) + "\n";

    for (auto it = start_it; it != end_it; it++) {
        current_vertex = it->first;
        if (graph.get_out_degree(current_vertex) == 0) {
            graph_str += std::to_string(current_vertex) + "\n";
        }
        else {
            std::pair<std::set<int>::iterator, std::set<int>::iterator> neighbours_start_end_it;
            neighbours_start_end_it = graph.get_outbound_neighbours(current_vertex);
            auto neighbours_start_it = neighbours_start_end_it.first;
            auto neighbours_end_it = neighbours_start_end_it.second;

            for (auto n_it = neighbours_start_it; n_it != neighbours_end_it; n_it++) {
                neighbour = *n_it;
                cost = graph.retrieve_cost_of_edge(current_vertex, neighbour);
                graph_str += std::to_string(current_vertex) + " " + std::to_string(neighbour) + " " + std::to_string(cost) + "\n";
            }

        }
    }
    fout << graph_str;
    fout.close();

}

Graph generate_random_graph(int nr_vertices, int nr_edges) {
    if (nr_vertices < 0 || nr_edges < 0) {
        throw GraphException("\nError! Nr. of edges/vertices must be positive.\n");
    }
    if (nr_edges > nr_vertices * (nr_vertices - 1)) {
        throw GraphException("\nError! Too many edges given.\n");
    }
    Graph random_graph = Graph(nr_vertices);
    int _from, _to, _cost;
    while (nr_edges) {
        _from = rand() % nr_vertices;
        _to = rand() % nr_vertices;
        _cost = (rand() % 200) - 100;   // Generate costs in the range [-100, 100)
        if (!random_graph.existence_edge(_from, _to)) {
            random_graph.add_edge(_from, _to, _cost);
            nr_edges -= 1;
        }
    }
    return random_graph;
}