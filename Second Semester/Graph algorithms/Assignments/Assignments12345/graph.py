import copy


class Graph:
    def __init__(self, vertices_counter=0, copies=None):
        """
        complexity: θ(1)
        Initialize a graph object.

        :type copies: object
        :param vertices_counter: Number of vertices in the graph. Default value is 0.
        :type vertices_counter: int

        This constructor initializes the following fields:
        - self.__vertices_counter: Number of vertices in the graph.
        - self.__edges_counter: Number of edges in the graph.
        - self.__out_edges: Dictionary that stores inbound edges of a vertex.
        - self.__in_edges: Dictionary that stores outbound edges of a vertex.
        - self.__edges_expense: Dictionary that stores the cost of an edge.
        """
        self.__vertices_counter = vertices_counter
        self.visited = [False] * vertices_counter
        self.originalVertex = 0
        self.hamPathVertices = []
        self.hamPathCost = 0
        self.__edges_counter = 0
        self.__out_edges = {}
        self.__in_edges = {}
        self.__edges_expense = {}
        self.__copy = copies

    def get_costs(self):
        return self.__edges_expense

    def get_out(self):
        return self.__out_edges

    def setter_for_vertices_counter(self, vertices_counter):
        """
        complexity: θ(1)
        Set the number of vertices in the graph.

        :param vertices_counter: The number of vertices with which to update the graph.
        :type vertices_counter: int

        This method updates the number of vertices in the graph with the specified value.
        """
        self.__vertices_counter = vertices_counter

    def getter_for_vertices_counter(self):
        """
        complexity: θ(1)
        Get the number of vertices in the graph.

        :return: The number of vertices of the graph.
        :type: int
        """
        return self.__vertices_counter

    def has_self_loop(self, node):
        """
        Check if the specified node has a self-loop.

        :param node: The node to check for a self-loop.
        :type node: int or str
        :return: True if the node has a self-loop, False otherwise.
        :rtype: bool
        """
        if node in self.__out_edges and node in self.__in_edges:
            return node in self.__out_edges[node] and node in self.__in_edges[node] and len(self.__in_edges[node]) == 1
        return False

    def getter_for_all_vertices(self):
        """
        complexity: θ(v), v - number of vertices
        Get the set of vertices in the graph.

        :return: The set of vertices of the graph.
        :rtype: set
        """
        return set(self.__out_edges.keys())

    def setter_of_the_number_of_edges(self, edges_counter):
        """
        complexity: O(1)
        Set the number of edges in the graph.

        :param edges_counter: The number of edges with which to update the graph.
        :type edges_counter: int

        This method updates the number of edges in the graph with the specified value.
        """
        self.__edges_counter = edges_counter

    def getter_of_the_extremities_of_edge(self, edge_id):
        """
        complexity: θ(v*e), where v - number of vertices, e - number of edges
        Retrieve the start and end nodes of the specified edge.

        :param edge_id: The ID of the edge for which we want to retrieve the start and end nodes.
        :type edge_id: int

        This method iterates through the outbound edges of each vertex to find the specified edge ID.
        If the edge ID is found, the method returns a tuple (start_node, end_node) representing the start and end nodes of the edge.
        If the edge does not exist, the method returns a tuple (-1, -1).

        :return: A tuple (start_node, end_node) representing the start and end nodes of the edge,
                 or (-1, -1) if the edge does not exist.
        :rtype: tuple
        """
        for start_node, child_edges in self.__in_edges.items():
            for end_node, current_edge_id in child_edges.items():
                if current_edge_id == edge_id:
                    return start_node, end_node
        return -1, -1

    def getter_id_of_edge(self, start_node, end_node):
        """
        complexity: θ(v+e) - where v is the number of vertices and e is the number of edges
        Retrieve the ID of the edge between the specified start and end nodes.

        :param start_node: The start node of the edge.
        :type start_node: int
        :param end_node: The end node of the edge.
        :type end_node: int
        :return: The ID of the edge between the specified start and end nodes, or -1 if the edge does not exist.
        :rtype: int
        """
        if start_node in self.__in_edges and end_node in self.__in_edges[start_node]:
            return self.__in_edges[start_node][end_node]
        return -1

    def getter_number_of_vertices(self):
        """
        complexity: O(1)
        Retrieve the number of edges in the graph.

        :return: The number of edges in the graph.
        :rtype: int
        """
        return self.__vertices_counter

    def getter_number_of_edges(self):
        """
        complexity: O(1)
        Retrieve the number of edges in the graph.

        :return: The number of edges in the graph.
        :rtype: int
        """
        return self.__edges_counter

    def get_child_edges(self):
        """
        complexity: O(v), where v - number of vertices
        Retrieve the outbound edges of the graph.

        :return: A dictionary containing the outbound edges of the graph, sorted by keys.
        :rtype: dict
        """
        return dict(sorted(self.__in_edges.items()))

    def get_parent_edges(self):
        """
        complexity: O(v), where v- number of vertices
        Retrieve the inbound edges of the graph.

        :return: A dictionary containing the inbound edges of the graph, sorted by keys.
        :rtype: dict
        """
        return dict(sorted(self.__out_edges.items()))

    def getter_int_degree_of_vertex(self, vertex):
        """
        Retrieve the in-degree of the specified vertex.

        :param vertex: The vertex for which to retrieve the in-degree.
        :type vertex: int
        :return: The in-degree of the specified vertex.
        :rtype: int
        """
        return len(self.__out_edges[vertex]) if vertex in self.__out_edges else 0

    def get_outbound_neighbors_with_costs(self, node):
        """
        Retrieve the outbound neighbors of the specified node along with the costs of the edges.

        :param node: The node for which to retrieve the outbound neighbors and costs.
        :type node: int or str
        :return: A list of tuples where each tuple contains the neighbor node and the cost of the edge.
        :rtype: list[(int or str, float)]
        """
        outbound_neighbors_with_costs = []
        if node in self.__out_edges:
            for neighbor, edge_id in self.__out_edges[node].items():
                cost = self.__edges_expense[edge_id]
                outbound_neighbors_with_costs.append((neighbor, cost))
        return outbound_neighbors_with_costs

    def getter_out_degree_of_vertex(self, v):
        """
        Retrieve the out-degree of the specified vertex.

        :param v: The vertex for which to retrieve the out-degree.
        :type v: int
        :return: The out-degree of the specified vertex.
        :rtype: int
        """
        return len(self.__in_edges[v]) if v in self.__in_edges else 0

    def getter_of_outbound_neighbours(self, v):
        """
        Retrieve the set of outbound neighbours of the specified vertex.

        :param v: The vertex for which to retrieve the outbound neighbours.
        :type v: int
        :return: The set of outbound neighbours of the specified vertex.
        :rtype: set[int]
        """
        if v in self.__in_edges:
            return sorted(set(self.__in_edges[v].keys()))
        else:
            return []

    def get_all_neighbours(self, v):
        inbound_neighbours = set()
        if v in self.__in_edges:
            inbound_neighbours.update(self.__in_edges[v].keys())
        if v in self.__out_edges:
            inbound_neighbours.update(self.__out_edges[v].keys())
        return sorted(inbound_neighbours)

    def getter_inbound_neighbours_near_vertex(self, v):
        """
        :param v: the vertex for which we want to retrieve the inbound neighbours

        :return: The set of unique inbound neighbours of the specified vertex.
        """
        if v in self.__out_edges:
            return set(self.__out_edges[v].keys())
        else:
            return set()

    def getter_the_cost_of_edge(self, edge_id):
        """
        Retrieve the cost associated with the specified edge.

        :param edge_id: The ID of the edge for which to retrieve the cost.
        :type edge_id: int or str
        :return: The cost of the specified edge.
        :rtype: float
        """
        return self.__edges_expense[edge_id]

    def getter_the_cost_of_edge_with_edges(self, _from, _to):
        """
        Retrieve the cost associated with the specified edge.

        :param edge_id: The ID of the edge for which to retrieve the cost.
        :type edge_id: int or str
        :return: The cost of the specified edge.
        :rtype: float
        """
        id = self.getter_id_of_edge(_from, _to)
        if id in self.__edges_expense.keys():
            return self.__edges_expense[id]
        else:
            id = self.getter_id_of_edge(_to, _from)
            return self.__edges_expense[id]

    def setter_the_cost_of_edge(self, edge_id, cost):
        """
        Set the cost associated with the specified edge.

        :param edge_id: The ID of the edge for which to set the cost.
        :type edge_id: int or str
        :param cost: The cost to be set for the specified edge.
        :type cost: float
        """
        self.__edges_expense[edge_id] = cost

    def checker_of_edge_existence(self, x, y):
        """
        complexity: θ(e+v), where v is the number of vertices and e number of edges
        :param x: the start node of the edge
        :param y: the end node of the edge
        :return: True if the edge (x, y) exists, False otherwise

        In order to check if an edge exists, we simply call the function getter_id_of_edge and check if it returns -1 or not
        """
        return self.getter_id_of_edge(x, y) != -1

    def adder_of_vertex_into_graph(self, v):
        """
        Add the specified vertex to the graph if it doesn't already exist.

        :param v: The vertex to add to the graph.
        :type v: int or str
        """
        if v not in self.__out_edges:
            self.__out_edges[v] = {}
            self.__in_edges[v] = {}

    def remover_of_vertex_from_graph(self, v):
        """
        Remove the specified vertex from the graph along with its associated edges.

        :param v: The vertex to remove from the graph.
        :type v: int or str
        """
        if v in self.__out_edges:
            self.__vertices_counter -= 1

            # Count the number of edges associated with this vertex
            num_edges = len(self.__out_edges[v]) + len(self.__in_edges[v])
            for x in list(self.__out_edges[v].values()):
                for y in list(self.__in_edges[v].values()):
                    if x == y:
                        num_edges -= 1

            # Decrement the edge counter by the number of edges being removed
            self.__edges_counter -= num_edges

            # Deleting parent edges
            parent_edges_copy = dict(self.__out_edges[v])
            for x in parent_edges_copy:
                del self.__edges_expense[parent_edges_copy[x]]
                del self.__in_edges[x][v]

            # Deleting child edges
            child_edges_copy = dict(self.__in_edges[v])
            for x in child_edges_copy:
                del self.__edges_expense[child_edges_copy[x]]
                del self.__out_edges[x][v]

            # Deleting vertex
            del self.__out_edges[v]
            del self.__in_edges[v]

    def adder_of_edge_to_graph(self, start_node, end_node, cost):
        """
        Add an edge to the graph between the specified start and end nodes with the given cost.

        If the start or end nodes do not exist in the graph, they will be added.

        :param start_node: The start node of the edge.
        :type start_node: int or str
        :param end_node: The end node of the edge.
        :type end_node: int or str
        :param cost: The cost associated with the edge.
        :type cost: float
        """
        self.adder_of_vertex_into_graph(start_node)
        self.adder_of_vertex_into_graph(end_node)
        self.__out_edges[end_node][start_node] = self.__edges_counter
        self.__in_edges[start_node][end_node] = self.__edges_counter
        self.__edges_expense[self.__edges_counter] = cost
        self.__edges_counter += 1

    def remover_of_edge_from_graph(self, start_node, end_node):
        """
        Remove the edge between the specified start and end nodes from the graph.

        :param start_node: The start node of the edge to remove.
        :type start_node: int or str
        :param end_node: The end node of the edge to remove.
        :type end_node: int or str
        """
        if self.checker_of_edge_existence(start_node, end_node):
            del self.__edges_expense[self.__in_edges[start_node][end_node]]
            del self.__in_edges[start_node][end_node]
            del self.__out_edges[end_node][start_node]
            self.__edges_counter -= 1

    def getter_of_copy_of_graph(self):
        """
        Return a deep copy of the graph.

        :return: A deep copy of the graph.
        :rtype: Graph
        """
        g = Graph(self.__vertices_counter)
        g.__out_edges = copy.deepcopy(self.__out_edges)
        g.__in_edges = copy.deepcopy(self.__in_edges)
        g.__edges_expense = copy.deepcopy(self.__edges_expense)
        g.__edges_counter = self.__edges_counter
        self.__copy = g

    def get_copy(self):
        return self.__copy

    def set_copy_of_graph(self):
        print(self.__copy)
        if self.__copy == None:
            return 1
        else:
            self.__out_edges = self.__copy.__out_edges
            self.__in_edges = self.__copy.__in_edges
            self.__edges_expense = self.__copy.__edges_expense
            self.__edges_counter = self.__copy.__edges_counter
            self.__vertices_counter = self.__copy.__vertices_counter
            return 0

    def setter_of_cost_on_edge(self, edge_id, cost):
        """
        Set the cost of the specified edge.

        :param edge_id: The ID of the edge for which to set the cost.
        :type edge_id: int or str
        :param cost: The cost of the edge.
        :type cost: float or int
        """
        self.__edges_expense[edge_id] = cost
