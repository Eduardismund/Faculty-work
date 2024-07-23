//
// Created by User on 3/10/2024.
//

#ifndef UNTITLED3_service_H
#define UNTITLED3_service_H

#endif //UNTITLED3_service_H

#include "Graph.h"

/*
    Reads the graph from a file, builds that graph, and returns it.
    Input: file_name - pointer to char, the name of the file
    Output: a new instance of the class <Graph>; the graph from the file
 */
Graph read_graph_from_file(char *file_name);

/*
    Writes the given graph to a file.
    Input: file_name - pointer to char, the name of the file
           graph - a reference to a graph object
 */
void write_graph_to_file(char *file_name, Graph& graph);

/*
    Creates a random graph with <nr_vertices> vertices and <nr_edges> edges.
    Input: nr_vertices - integer, the number of vertices
           nr_edges - integer, the number of edges
    Output: a new instance of the class <Graph>, the randomly generated graph
 */
Graph generate_random_graph(int nr_vertices, int nr_edges);
