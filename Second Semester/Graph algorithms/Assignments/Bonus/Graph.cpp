//
// Created by VladB on 18-Mar-21.
//

#include "Graph.h"
#include "exceptions.h"

/**
 * @brief Constructs a graph with the specified number of vertices.
 *
 * This constructor initializes a graph with the specified number of vertices.
 * It creates empty sets of outbound and inbound neighbors for each vertex.
 *
 * @param v_no The number of vertices in the graph.
 */
Graph::Graph(int v_no) {
    // Initialize the graph with the specified number of vertices
    for (int i = 0; i < v_no; i++) {
        this->out_edges_dict[i] = std::set<int>();
        this->in_edges_dict[i] = std::set<int>();
    }
}


/**
 * O(1)
 * @brief Retrieves the number of vertices in the graph.
 *
 * This method retrieves the number of vertices in the graph by returning
 * the size of the out_edges_dict map, which contains the vertices as keys.
 *
 * @return The number of vertices in the graph.
 */
int Graph::retrieve_vertex_count() const {
    return this->out_edges_dict.size();
}


/**
 * O(1)
 * @brief Retrieves the number of edges in the graph.
 *
 * This method retrieves the number of edges in the graph by returning
 * the size of the costs map, which contains the edges as key-value pairs.
 *
 * @return The number of edges in the graph.
 */
int Graph::retrieve_edges_count() const {
    return this->costs.size();
}


/**
 * @brief Retrieves iterators representing the range of outbound relations in the graph.
 *
 * This method retrieves iterators representing the range of outbound relations in the graph.
 * It returns a pair of iterators, where the first iterator points to the beginning of the
 * out_edges_dict map and the second iterator points to one past the end of the map.
 *
 * @return A pair of iterators representing the range of outbound relations in the graph.
 */
std::pair<std::map<int, std::set<int>>::iterator, std::map<int, std::set<int>>::iterator>
Graph::out_relations() {
    return std::make_pair(this->out_edges_dict.begin(), this->out_edges_dict.end());
}


/**
 * @brief Retrieves iterators representing the range of all edges in the graph.
 *
 * This method retrieves iterators representing the range of all edges in the graph.
 * It returns a pair of iterators, where the first iterator points to the beginning of the
 * costs map and the second iterator points to one past the end of the map.
 *
 * @return A pair of iterators representing the range of all edges in the graph.
 */
std::pair<std::map<std::pair<int, int>, int>::iterator, std::map<std::pair<int, int>, int>::iterator>
Graph::get_all_edges() {
    return std::make_pair(this->costs.begin(), this->costs.end());
}


/**
 * O(log e), e - edges
 * @brief Checks if an edge exists between two vertices.
 *
 * This method checks if there exists an edge from vertex _from to vertex _to in the graph.
 * It does so by searching for the edge in the costs map using the pair (_from, _to) as the key.
 * If the edge exists in the costs map, this method returns true, otherwise, it returns false.
 *
 * @param _from The source vertex of the edge.
 * @param _to The destination vertex of the edge.
 * @return true if the edge exists, false otherwise.
 */
bool Graph::existence_edge(int _from, int _to) {
    return this->costs.find(std::make_pair(_from, _to)) != this->costs.end();
}


/**
 * @brief Retrieves the cost of an edge between two vertices.
 *
 * This method retrieves the cost associated with the edge from vertex _from to vertex _to in the graph.
 * It first checks if the edge exists in the graph using the existence_edge() method.
 * If the edge does not exist, it throws a GraphException.
 * Otherwise, it returns the cost associated with the edge from the costs map.
 *
 * @param _from The source vertex of the edge.
 * @param _to The destination vertex of the edge.
 * @return The cost of the edge from vertex _from to vertex _to.
 *
 * @throw GraphException If the edge is not in the graph.
 */
int Graph::retrieve_cost_of_edge(int _from, int _to) {
    // Check if the edge exists in the graph
    if (!this->existence_edge(_from, _to)) {
        throw GraphException("Error! The edge is not in the graph.");
    }
    // Return the cost associated with the edge
    return this->costs[std::make_pair(_from, _to)];
}


/**
 * @brief Checks if a vertex is in the graph.
 *
 * This method checks if the specified vertex is present in the graph.
 * It does so by searching for the vertex in the out_edges_dict map.
 * If the vertex is found in the map, this method returns true, otherwise, it returns false.
 *
 * @param vertex The vertex to check for existence in the graph.
 * @return true if the vertex is in the graph, false otherwise.
 */
bool Graph::is_vertex_in_graph(int vertex) {
    return this->out_edges_dict.find(vertex) != this->out_edges_dict.end();
}


/**
 * @brief Retrieves the in-degree of a vertex in the graph.
 *
 * This method retrieves the in-degree of the specified vertex in the graph.
 * It first checks if the vertex is in the graph using the is_vertex_in_graph() method.
 * If the vertex is not in the graph, it throws a GraphException.
 * Otherwise, it returns the size of the set of inbound neighbors for the vertex,
 * which represents the in-degree of the vertex.
 *
 * @param vertex The vertex for which to retrieve the in-degree.
 * @return The in-degree of the vertex.
 *
 * @throw GraphException If the vertex is not in the graph.
 */
int Graph::get_in_degree(int vertex) {

    if(vertex>this->costs.size())
        throw GraphException("\nError! The vertex is not in the graph.\n");
    return this->in_edges_dict[vertex].size();
}


/**
 * @brief Retrieves the out-degree of a vertex in the graph.
 *
 * This method retrieves the out-degree of the specified vertex in the graph.
 * It first checks if the vertex is in the graph using the is_vertex_in_graph() method.
 * If the vertex is not in the graph, it throws a GraphException.
 * Otherwise, it returns the size of the set of outbound neighbors for the vertex,
 * which represents the out-degree of the vertex.
 *
 * @param vertex The vertex for which to retrieve the out-degree.
 * @return The out-degree of the vertex.
 *
 * @throw GraphException If the vertex is not in the graph.
 */
int Graph::get_out_degree(int vertex) {
    if(vertex>=this->costs.size())
        throw GraphException("\nError! The vertex is not in the graph.\n");
    return this->out_edges_dict[vertex].size();
}


/**
 * @brief Retrieves iterators representing the range of outbound neighbors for a given vertex.
 *
 * This method retrieves iterators representing the range of outbound neighbors for the specified vertex.
 * It first checks if the vertex is in the graph using the is_vertex_in_graph() method.
 * If the vertex is not in the graph, it throws a GraphException.
 * Otherwise, it returns a pair of iterators, where the first iterator points to the beginning of the
 * outbound neighbors set for the vertex and the second iterator points to one past the end of the set.
 *
 * @param vertex The vertex for which to retrieve the range of outbound neighbors.
 * @return A pair of iterators representing the range of outbound neighbors for the vertex.
 *
 * @throw GraphException If the vertex is not in the graph.
 */
std::pair<std::set<int>::iterator, std::set<int>::iterator>
Graph::get_outbound_neighbours(int vertex) {
    // Check if the vertex is in the graph
    if (!this->is_vertex_in_graph(vertex)) {
        throw GraphException("\nError! The vertex is not in the graph.\n");
    }
    // Return a pair of iterators representing the range of outbound neighbors for the vertex
    return std::make_pair(this->out_edges_dict[vertex].begin(), this->out_edges_dict[vertex].end());
}


/**
 * @brief Retrieves iterators representing the range of inbound neighbors for a given vertex.
 *
 * This method retrieves iterators representing the range of inbound neighbors for the specified vertex.
 * It first checks if the vertex is in the graph. If the vertex is not in the graph, it throws a GraphException.
 * Otherwise, it returns a pair of iterators, where the first iterator points to the beginning of the
 * inbound neighbors set for the vertex and the second iterator points to one past the end of the set.
 *
 * @param vertex The vertex for which to retrieve the range of inbound neighbors.
 * @return A pair of iterators representing the range of inbound neighbors for the vertex.
 *
 * @throw GraphException If the vertex is not in the graph.
 */
std::pair<std::set<int>::iterator, std::set<int>::iterator>
Graph::get_inbound_neighbours(int vertex) {
    // Check if the vertex is in the graph
    if (!this->is_vertex_in_graph(vertex)) {
        throw GraphException("\nError! The vertex is not in the graph.\n");
    }
    // Return a pair of iterators representing the range of inbound neighbors for the vertex
    return std::make_pair(this->in_edges_dict[vertex].begin(), this->in_edges_dict[vertex].end());
}


/**
 * @brief Adds a vertex to the graph.
 *
 * This method adds the specified vertex to the graph. It first checks if the vertex
 * is already in the graph. If the vertex is already in the graph, it throws a GraphException
 * with an appropriate error message. Otherwise, it adds the vertex to the out_edges_dict
 * and in_edges_dict maps, initializing the sets of outbound and inbound neighbors for the vertex.
 *
 * @param vertex The vertex to be added to the graph.
 *
 * @throw GraphException If the vertex is already in the graph.
 */
void Graph::add_vertex(int vertex) {
    // If the vertex is already in the graph, throw an exception
    if (this->is_vertex_in_graph(vertex)) {
        throw GraphException("\nError! The vertex is already in the graph.\n");
    }
    // Add the vertex to the out_edges_dict and in_edges_dict maps
    // Initialize the sets of outbound and inbound neighbors for the vertex
    this->out_edges_dict[vertex] = std::set<int>();
    this->in_edges_dict[vertex] = std::set<int>();
}


/**
 * @brief Removes a vertex from the graph.
 *
 * This method removes the specified vertex from the graph. It first checks if the vertex is in the graph.
 * If the vertex is not in the graph, it throws a GraphException with an appropriate error message.
 * Otherwise, it removes the sets of neighbors (inbound and outbound) of the vertex, removes any appearance
 * of the vertex in the neighbors of other vertices, and removes any key-value pair in the costs map
 * involving the given vertex.
 *
 * @param vertex The vertex to be removed from the graph.
 *
 * @throw GraphException If the vertex is not in the graph.
 */
void Graph::remove_vertex(int vertex) {
    // If the vertex is not in the graph, throw an exception
    if (!this->is_vertex_in_graph(vertex)) {
        throw GraphException("\nError! The vertex is not in the graph.\n");
    }
    // Remove the sets of neighbors (inbound and outbound) of the vertex
    this->out_edges_dict.erase(vertex);
    this->in_edges_dict.erase(vertex);
    // Remove any appearance of vertex in the outbound and inbound neighbors of other vertices
    for (auto &it : this->out_edges_dict) {
        it.second.erase(vertex);
    }
    for (auto &it: this->in_edges_dict) {
        it.second.erase(vertex);
    }
    // Remove any key-value pair in costs involving the given vertex
    auto it = this->costs.begin();
    while (it != this->costs.end()) {
        if (it->first.first == vertex || it->first.second == vertex) {
            it = this->costs.erase(it);
        } else {
            it++;
        }
    }
}


/**
 * @brief Adds an edge between two vertices with the specified cost.
 *
 * This method adds an edge from vertex _from to vertex _to with the specified cost _cost
 * to the graph. It first checks if both vertices are in the graph and if the edge already exists.
 * If either condition is not met, it throws a GraphException with an appropriate error message.
 * Otherwise, it adds the edge to the in_edges_dict, out_edges_dict, and costs map.
 *
 * @param _from The source vertex of the edge to be added.
 * @param _to The destination vertex of the edge to be added.
 * @param _cost The cost associated with the edge.
 *
 * @throw GraphException If either of the vertices is not in the graph or the edge already exists.
 */
void Graph::add_edge(int _from, int _to, int _cost) {
    // If one of the vertices of the given edge is not in the graph, throw an exception
    if (!this->is_vertex_in_graph(_from) || !this->is_vertex_in_graph(_to)) {
        throw GraphException("\nError! Both vertices must be in the graph.\n");
    }
    // If the edge already exists, throw an exception
    if (this->existence_edge(_from, _to)) {
        throw GraphException("\nError! The edge is already in the graph.\n");
    }
    // Add the vertex _to in the out_edges_dict set of _from
    // Add the vertex _from in the in_edges_dict set of _to
    // Add the edge in costs
    this->in_edges_dict[_to].insert(_from);
    this->out_edges_dict[_from].insert(_to);
    this->costs[std::make_pair(_from, _to)] = _cost;
}


/**
 * @brief Removes an edge between two vertices.
 *
 * This method removes the edge from vertex _from to vertex _to from the graph.
 * It first checks if both vertices are in the graph and if the edge exists between them.
 * If either condition is not met, it throws a GraphException with an appropriate error message.
 * Otherwise, it removes the edge from the in_edges_dict, out_edges_dict, and costs map.
 *
 * @param _from The source vertex of the edge to be removed.
 * @param _to The destination vertex of the edge to be removed.
 *
 * @throw GraphException If either of the vertices is not in the graph or the edge does not exist.
 */
void Graph::remove_edge(int _from, int _to) {
    // If one of the vertices of the given edge is not in the graph, throw an exception
    if (!this->is_vertex_in_graph(_from) || !this->is_vertex_in_graph(_to)) {
        throw GraphException("\nError! Both vertices must be in the graph.\n");
    }
    // If the edge is not in the graph, throw an exception
    if (!this->existence_edge(_from, _to)) {
        throw GraphException("\nError! The edge is not in the graph.\n");
    }
    // Remove _from from in_edges_dict[_to], _to from out_edges_dict[_from], and the element with key (_from, _to) from costs
    this->in_edges_dict[_to].erase(_from);
    this->out_edges_dict[_from].erase(_to);
    this->costs.erase(std::make_pair(_from, _to));
}


/**
 * @brief Changes the cost of the edge between two vertices.
 *
 * This method changes the cost of the edge from vertex _from to vertex _to
 * to the specified new_cost. It first checks if both vertices are in the graph
 * and if the edge exists between them. If either condition is not met, it throws
 * a GraphException with an appropriate error message.
 *
 * @param _from The source vertex of the edge.
 * @param _to The destination vertex of the edge.
 * @param _new_cost The new cost to be assigned to the edge.
 *
 * @throw GraphException If either of the vertices is not in the graph or the edge does not exist.
 */
void Graph::change_cost(int _from, int _to, int _new_cost) {
    // If one of the vertices of the given edge is not in the graph, throw an exception
    if (!this->is_vertex_in_graph(_from) || !this->is_vertex_in_graph(_to)) {
        throw GraphException("\nError! Both vertices must be in the graph.\n");
    }
    // If the edge is not in the graph, throw an exception
    if (!this->existence_edge(_from, _to)) {
        throw GraphException("\nError! The edge is not in the graph.\n");
    }
    // Change the cost of the edge
    this->costs[std::make_pair(_from, _to)] = _new_cost;
}


/**
 * @brief Creates a deep copy of the current graph.
 *
 * This method creates a new graph that is a deep copy of the current graph.
 * It copies all vertices, edges, and associated costs from the current graph
 * to the new graph. The new graph is completely independent of the original graph.
 *
 * @return A new graph that is a deep copy of the current graph.
 */
Graph Graph::copy_graph() {
    Graph new_graph = Graph(this->retrieve_vertex_count());

    for (auto &cost : this->costs) {
        new_graph.costs[std::make_pair(cost.first.first, cost.first.second)] = cost.second;
    }

    for (auto &map_it : this->in_edges_dict) {
        for (auto set_it = map_it.second.begin(); set_it != map_it.second.end(); set_it++) {
            new_graph.in_edges_dict[map_it.first].insert(*set_it);
        }
    }

    for (auto &map_it : this->out_edges_dict) {
        for (auto set_it = map_it.second.begin(); set_it != map_it.second.end(); set_it++) {
            new_graph.out_edges_dict[map_it.first].insert(*set_it);
        }
    }

    return new_graph;
}
/**
 * @brief Checks if the graph is empty.
 *
 * This method checks if the graph is empty, i.e., if it contains no vertices or edges.
 * It returns true if the graph is empty (i.e., if both the out_edges_dict, in_edges_dict, and costs maps are empty),
 * and false otherwise.
 *
 * @return true if the graph is empty, false otherwise.
 */
bool Graph::isEmpty() const {
    return this->out_edges_dict.empty() && this->in_edges_dict.empty() && this->costs.empty();
}

