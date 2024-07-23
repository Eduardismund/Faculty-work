//
// Created by User on 3/10/2024.
//

#ifndef UNTITLED3_ui_H
#define UNTITLED3_ui_H

#endif //UNTITLED3_ui_H

#include "Graph.h"

class UI {
private:
    Graph &graph;
    Graph newGraph;


    static void print_menu();

    void ui_get_number_of_vertices();

    void ui_get_number_of_edges();

    void ui_get_vertices();

    void ui_get_edges();

    void ui_check_vertex();

    void ui_check_edge();

    void ui_get_cost_of_edge();

    void ui_in_degree_of_vertex();

    void ui_out_degree_of_vertex();

    void ui_outbound_neighbours();

    void ui_inbound_neighbours();

    void ui_change_edge_cost();

    void ui_add_edge();

    void ui_remove_edge();

    void ui_add_vertex();

    void ui_remove_vertex();

    void ui_write_graph_to_file();

    void ui_read_graph_from_file();

    void ui_generate_random_graph();

public:
    explicit UI(Graph &graph);

    void run_app();

    void ui_copy_graph();
};
