//
// Created by User on 3/10/2024.
//

#ifndef UNTITLED3_Graph_H
#define UNTITLED3_Graph_H

#include <map>
#include <set>
#include <iterator>

class Graph {
private:
    std::map<int, std::set<int>> out_edges_dict;
    std::map<int, std::set<int>> in_edges_dict;
    std::map<std::pair<int, int>, int> costs;
public:

    explicit Graph(int nr_vertices = 0);
    int retrieve_vertex_count() const;
    int retrieve_edges_count() const;
    std::pair<std::map<int, std::set<int>>::iterator, std::map<int, std::set<int>>::iterator> out_relations();
    std::pair<std::map<std::pair<int, int>, int>::iterator, std::map<std::pair<int, int>, int>::iterator> get_all_edges();
    bool existence_edge(int _from, int _to);
    int retrieve_cost_of_edge(int _from, int _to);
    bool is_vertex_in_graph(int vertex);
    int get_in_degree(int vertex);
    int get_out_degree(int vertex);
    std::pair<std::set<int>::iterator, std::set<int>::iterator> get_outbound_neighbours(int vertex);
    std::pair<std::set<int>::iterator, std::set<int>::iterator> get_inbound_neighbours(int vertex);
    void add_vertex(int vertex);
    void remove_vertex(int vertex);
    void add_edge(int _from, int _to, int _cost);
    void remove_edge(int _from, int _to);
    void change_cost(int _from, int _to, int _new_cost);
    Graph copy_graph();
    bool isEmpty() const;
};

#endif