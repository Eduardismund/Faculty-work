from graph import Graph
from random import randint
from queue import PriorityQueue
import sys

INF = sys.maxsize


class Controller:
    def __init__(self):
        """
        Constructor for the Controller class.

        Initializes a graph object that will be used for algorithms.
        """
        self.graph = Graph()
        self.visited = [False] * self.graph.getter_number_of_vertices()
        self.cycle = []
        self.copy = None


    def set_up(self):
        self.visited = [False] * self.graph.getter_number_of_vertices()
        self.cycle = []
    def read_graph_from_file(self, filename):
        """
        Read the graph from a file and add edges to the graph.

        :param filename: The name of the file from which to read the graph.
        :type filename: str
        """
        with open(filename, "r") as file:
            v, e = map(int, file.readline().split())
            self.graph = Graph(v)
            for i in range(e):
                edge_id = i
                cost = 0
                start_node, end_node, cost = map(int, file.readline().split())
                self.graph.adder_of_edge_to_graph(start_node, end_node, cost)

    def write_graph_to_file(self, filename):
        """
        Write the graph to a file.

        :param filename: The name of the file to which to write the graph.
        :type filename: str
        """
        with open(filename, "w") as file:
            file.write(f"{self.graph.getter_for_vertices_counter()} {self.graph.getter_number_of_edges()}\n")
            out_edges = self.graph.get_child_edges()
            for x in out_edges:
                for y in out_edges[x]:
                    file.write(f"{x} {y} {self.graph.getter_the_cost_of_edge(out_edges[x][y])}\n")

    def generate_random_graph(self, nr_of_vertices, nr_of_edges):
        """
        Generate a random graph.

        :param nr_of_vertices: The number of vertices of the graph.
        :type nr_of_vertices: int
        :param nr_of_edges: The number of edges of the graph.
        :type nr_of_edges: int
        """
        copy = self.graph.get_copy()
        self.graph = Graph(nr_of_vertices, copy)
        for i in range(nr_of_edges):
            start_node = randint(0, nr_of_vertices - 1)
            end_node = randint(0, nr_of_vertices - 1)
            while self.graph.checker_of_edge_existence(start_node, end_node):
                start_node = randint(0, nr_of_vertices - 1)
                end_node = randint(0, nr_of_vertices - 1)
            self.graph.adder_of_edge_to_graph(start_node, end_node, i)
            self.graph.setter_of_cost_on_edge(i, randint(1, 100))

    def forward_bfs(self, start_node, end_node):
        """
        This function finds the shortest path between two nodes in a directed graph using a forward breadth-first search, starting from the start node.
        :param start_node: the start node
        :param end_node: the end node
        :return: the shortest path between the two nodes
        """
        visited = [False] * self.graph.getter_for_vertices_counter()
        queue = []
        exists_a_path = False
        queue.append(start_node)
        visited[start_node] = True
        parent = [None] * self.graph.getter_for_vertices_counter()
        out_edges = self.graph.get_child_edges()
        while queue:
            node = queue.pop(0)
            if node == end_node:
                exists_a_path = True
                break
            for neighbour in out_edges[node]:  # Traverse out edges for forward BFS
                if not visited[neighbour]:
                    queue.append(neighbour)
                    visited[neighbour] = True
                    parent[neighbour] = node
        if not exists_a_path:  # Simplified condition check
            return []
        path = []
        node = end_node  # Start reconstructing path from the end node
        while node != start_node:
            path.append(node)
            node = parent[node]
        path.append(start_node)  # Add the start node to complete the path
        return path[::-1]  # Reverse the path to get it in the forward direction


    """
    Homework for practical work 3
    Write a program that, given a graph with costs and two vertices, finds a lowest cost walk between the 
    given vertices, or prints a message if there are negative cost cycles accessible from the starting vertex. 
    The program will use a matrix defined as d[x,k]=the cost of the lowest cost walk from s to x and 
    of length at most k, where s is the starting vertex.
    """

    def lowest_cost_walk(self, start_vertex, end_vertex):
        infinity = 9999999999

        n = self.graph.getter_for_vertices_counter()
        d = [[infinity for _ in range(n)] for _ in range(n)]
        p = [[None for _ in range(n)] for _ in range(n)]

        d[start_vertex][0] = 0


        for k in range(1, n):
            for x in self.graph.getter_for_all_vertices():
                d[x][k] = d[x][k - 1]
                p[x][k] = p[x][k - 1]
                for y in self.graph.getter_inbound_neighbours_near_vertex(x):
                    if d[y][k - 1] + self.graph.getter_the_cost_of_edge(self.graph.getter_id_of_edge(y, x)) < d[x][k]:
                        d[x][k] = d[y][k - 1] + self.graph.getter_the_cost_of_edge(self.graph.getter_id_of_edge(y, x))
                        p[x][k] = y

        for x in range(n):
            if d[x][n - 1] != d[x][n - 2]:
                raise Exception("The graph contains a negative cost cycle!")

        if d[end_vertex][n - 1] == infinity:
            raise Exception("There is no path between the given vertices!")

        path = []
        current_vertex = end_vertex
        k = n - 1
        while current_vertex is not None:
            path.append(current_vertex)
            current_vertex = p[current_vertex][k]
            k -= 1

        path.reverse()

        return d[end_vertex][n - 1], path

    def prim_algorithm(self, start):
        """
        Find the minimum spanning tree (MST) of the graph starting from the given vertex <start> using
        Prim's Algorithm.
        :param start: The vertex where we want Prim's Algorithm to start from; integer
        :return: The edges from the minimum spanning tree; list of pairs representing the edges: (_from, _to)
        """
        if start not in self.graph.getter_for_all_vertices():
            raise ValueError(f"The vertex {start} does not exist in the graph.")

        q = PriorityQueue()
        prev = {node: None for node in self.graph.getter_for_all_vertices()}
        dist = {node: float('inf') for node in self.graph.getter_for_all_vertices()}
        processed = {node: False for node in self.graph.getter_for_all_vertices()}
        tree_edges = []

        dist[start] = 0
        processed[start] = True

        for neighbour in self.graph.get_all_neighbours(start):
            dist[neighbour] = self.graph.getter_the_cost_of_edge_with_edges( neighbour, start)
            prev[neighbour] = start
            q.put((dist[neighbour], neighbour))

        while not q.empty():
            top = q.get()
            top_vertex = top[1]
            if not processed[top_vertex]:
                tree_edges.append((prev[top_vertex], top_vertex))
                processed[top_vertex] = True
                for neighbour in self.graph.get_all_neighbours(top_vertex):
                    if not processed[neighbour] and self.graph.getter_the_cost_of_edge_with_edges( neighbour, top_vertex) < dist[neighbour]:
                        dist[neighbour] = self.graph.getter_the_cost_of_edge_with_edges(neighbour, top_vertex)
                        q.put((dist[neighbour], neighbour))
                        prev[neighbour] = top_vertex

        return tree_edges

    def DFSNearestNeighbour(self, sourceVertex, cycleLength):
        self.graph.visited[sourceVertex] = True
        outboundNeighbours = self.graph.get_child_edges()[sourceVertex]
        sorted_items=sorted(outboundNeighbours.items(), key=lambda item:self.graph.get_costs()[item[1]])
        hasFoundOriginalVertex = False

        for neighbour in sorted_items:
            if neighbour[0] == self.graph.originalVertex and cycleLength == self.graph.getter_number_of_vertices() - 1:
                self.graph.hamPathVertices.append(sourceVertex)
                self.graph.hamPathCost += self.graph.get_costs()[neighbour[1]]
                return True

            elif not self.graph.visited[neighbour[0]]:
                hasFoundOriginalVertex = self.DFSNearestNeighbour(neighbour[0], cycleLength + 1)
                if hasFoundOriginalVertex:
                    self.graph.hamPathVertices.append(sourceVertex)
                    self.graph.hamPathCost += self.graph.get_costs()[neighbour[1]]
                    return True

        self.graph.visited[sourceVertex] = False
        return hasFoundOriginalVertex

    def approximateTSPNearestNeighbour(self):
        self.graph.originalVertex = 0
        self.graph.hamPathCost = 0

        self.graph.visited = [False] * self.graph.getter_number_of_vertices()

        self.DFSNearestNeighbour(self.graph.originalVertex, 0)