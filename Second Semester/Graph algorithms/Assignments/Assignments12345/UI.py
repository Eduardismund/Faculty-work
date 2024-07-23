from service import Controller


class UI:
    def __init__(self):
        self.__controller = Controller()

    def print_graph(self):
        """
        Print the graph to the console.

        This function prints the number of vertices and edges of the graph,
        followed by the details of each edge, including its ID, start node,
        end node, and cost.
        """
        print(
            f"{self.__controller.graph.getter_for_vertices_counter()} {self.__controller.graph.getter_number_of_edges()}")
        child_edges = self.__controller.graph.get_child_edges()
        for x in child_edges:
            for y in child_edges[x]:
                print(
                    f"{child_edges[x][y]}) {x}->{y} {self.__controller.graph.getter_the_cost_of_edge(child_edges[x][y])}")

    def print_vertices(self):
        """
        Print the vertices of the graph.

        This function retrieves all vertices from the graph and prints them to the console.
        """
        vertices = self.__controller.graph.getter_for_all_vertices()
        print("The vertices of the graph are:")
        for vertex in vertices:
            print(vertex)

    def check_if_edge_exists(self):
        """
        Display a console menu for checking the existence of an edge in the graph.

        This function prompts the user to input two vertices and checks if an edge exists between them.
        """
        try:
            x, y = map(int, input("Please enter the IDs of the two vertices separated by space: ").split())
        except ValueError:
            print("Invalid input! Please enter integers only.")
            return

        if self.__controller.graph.checker_of_edge_existence(x, y):
            print(
                f"There is an edge from vertex {x} to vertex {y}, having the index: {self.__controller.graph.getter_id_of_edge(x, y)}")
        else:
            print(f"There is no edge from vertex {x} to vertex {y}.")

    def get_in_degree_and_out_degree(self):
        """
        Display a console menu for obtaining the in-degree and out-degree of a specified vertex.

        This function prompts the user to input a vertex ID and retrieves its in-degree and out-degree from the graph.
        """
        try:
            v = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        in_degree = self.__controller.graph.getter_int_degree_of_vertex(v)
        out_degree = self.__controller.graph.getter_out_degree_of_vertex(v)

        print(f"The in-degree of vertex {v} is {in_degree}.")
        print(f"The out-degree of vertex {v} is {out_degree}.")

    def parse_outbound_edges(self):
        """
        Display a console menu for parsing and printing outbound edges of a specified vertex.

        This function prompts the user to enter a vertex ID.
        It then retrieves the outbound edges of the specified vertex from the graph and prints them to the console.
        """
        try:
            vertex = int(input("Please enter the vertex ID: "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        out_edges = self.__controller.graph.get_child_edges()
        if vertex in out_edges:
            if len(out_edges[vertex]) == 0:
                print(f"There are no outbound edges for vertex {vertex}.")
            else:
                print(f"The outbound edges of vertex {vertex} are:")
                for end_vertex, edge_id in out_edges[vertex].items():
                    cost = self.__controller.graph.getter_the_cost_of_edge(edge_id)
                    print(f"Edge ID: {edge_id}, Start vertex: {vertex}, End vertex: {end_vertex}, Cost: {cost}")
        else:
            print(f"There are no outbound edges for vertex {vertex}.")

    def parse_inbound_edges(self):
        """
        Display a console menu for parsing and printing inbound edges of a specified vertex.

        This function prompts the user to input a vertex ID.
        It then retrieves the inbound edges of the specified vertex from the graph and prints them to the console.
        """
        try:
            vertex = int(input("Please enter the vertex ID: "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        in_edges = self.__controller.graph.get_parent_edges()
        if vertex in in_edges:
            if len(in_edges[vertex]) == 0:
                print(f"There are no inbound edges for vertex {vertex}.")
            else:
                print(f"The inbound edges of vertex {vertex} are:")
                for start_vertex, edge_id in in_edges[vertex].items():
                    cost = self.__controller.graph.getter_the_cost_of_edge(edge_id)
                    print(f"Edge ID: {edge_id}, Start vertex: {start_vertex}, End vertex: {vertex}, Cost: {cost}")
        else:
            print(f"There are no inbound edges for vertex {vertex}.")

    def getter_of_the_extremities_of_edge(self):
        """
        Display the endpoints of a specified edge.

        This function prompts the user to input an edge ID.
        It then retrieves and prints the endpoints of the specified edge from the graph.
        """
        try:
            edge_id = int(input("Please enter the edge ID: "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        start_vertex, end_vertex = self.__controller.graph.getter_of_the_extremities_of_edge(edge_id)
        if start_vertex == -1:
            print(f"There is no edge with ID {edge_id}.")
        else:
            print(f"The endpoints of edge {edge_id} are {start_vertex} and {end_vertex}.")

    def modify_cost_of_edge(self):
        """
        Modify the cost of a specified edge.

        This function prompts the user to input the ID of the edge and the new cost.
        It then modifies the cost of the specified edge in the graph.
        """
        try:
            edge_id = int(input("Which edge's cost do you want to modify? "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        try:
            new_cost = int(input("What is the new cost? "))
        except ValueError:
            print("Invalid input! Please enter an integer.")
            return

        self.__controller.graph.setter_the_cost_of_edge(edge_id, new_cost)
        print(f"The cost of edge {edge_id} has been modified to {new_cost}.")

    def add_edge(self):
        """
        Add an edge to the graph.

        This function provides a menu to add an edge to the graph.
        If the graph is empty, the user MUST provide the number of vertices first.
        In case the user adds an edge with a vertex that does not exist, the vertex will be added to the graph.
        The vertices MUST BE smaller than n - 1 and greater than 0.
        """
        if self.__controller.graph.getter_for_vertices_counter() == 0:
            print("First, you have to add vertices before you can add an edge!")
            return

        try:
            x, y, cost = input("Please enter the 2 vertices and the cost: ").split()
            x, y, cost = int(x), int(y), int(cost)
        except ValueError:
            print("Invalid input! Please enter integers for vertices and cost.")
            return

        vertices_counter = self.__controller.graph.getter_for_vertices_counter()
        if x >= vertices_counter or y >= vertices_counter:
            print(f"The provided vertices MUST BE between 0 and {vertices_counter - 1}. Try again!")
        elif self.__controller.graph.checker_of_edge_existence(x, y):
            print(f"There is already an edge from {x} to {y}.")
        else:
            self.__controller.graph.adder_of_edge_to_graph(x, y, cost)
            print(f"The edge from {x} to {y} with cost {cost} has been added.")

    def remove_edge(self):
        """
        Remove an edge from the graph.

        This function provides a menu to remove an edge from the graph.
        If the graph is empty, the operation cannot be performed.
        """
        if self.__controller.graph.getter_for_vertices_counter() == 0:
            print("First, you have to add vertices before you can remove an edge!")
            return

        try:
            x, y = input("Please enter the 2 vertices: ").split()
            x, y = int(x), int(y)
        except ValueError:
            print("Invalid input! Please enter integers for vertices.")
            return

        if self.__controller.graph.checker_of_edge_existence(x, y):
            self.__controller.graph.remover_of_edge_from_graph(x, y)
            print(f"The edge from {x} to {y} has been removed!")
        else:
            print(f"There is no edge from {x} to {y}.")

    def add_vertex(self):
        """
        Add a vertex to the graph.

        This function provides a menu to add a vertex to the graph.
        If the graph is empty, the user MUST provide the number of vertices first.
        In case the user adds a vertex that already exists, the operation will have no effect on the graph.
        """
        if self.__controller.graph.getter_for_vertices_counter() == 0:
            try:
                vertices_count = int(input("The graph is empty! Please provide the number of vertices: "))
            except ValueError:
                print("Invalid input! Please enter an integer for the number of vertices.")
                return
            self.__controller.graph.setter_for_vertices_counter(vertices_count)

        try:
            vertex = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input! Please enter an integer for the vertex.")
            return

        self.__controller.graph.adder_of_vertex_into_graph(vertex)
        print("Vertex added successfully!")

    def remove_vertex(self):
        """
        Remove a vertex from the graph.

        This function provides a menu to remove a vertex from the graph.
        """
        try:
            vertex = int(input("Please enter the vertex: "))
        except ValueError:
            print("Invalid input! Please enter an integer for the vertex.")
            return

        self.__controller.graph.remover_of_vertex_from_graph(vertex)
        print("Vertex removed successfully!")

    def copy_graph(self):
        """
        Copy the graph.

        This function creates a copy of the graph.
        """
        option = int(
            input("Insert:\n\t1-if you want to restore an already copied Graph\n\t2-if you want to copy this graph:\n"))
        if option == 2:
            self.__controller.graph.getter_of_copy_of_graph()
            print("Graph copied successfully!")
        elif option == 1:
            ok = self.__controller.graph.set_copy_of_graph()
            if ok == 1:
                print("You have not made any copies.")
            else:
                print("Graph copied successfully!")

    def print_the_cost(self):
        """
        Print the cost of a specified edge.

        This function prompts the user to enter the ID of an edge and then prints its cost.
        """
        try:
            edge_id = int(input("Please enter the ID of the edge: "))
        except ValueError:
            print("Invalid input! Please enter an integer for the edge ID.")
            return

        cost = self.__controller.graph.getter_the_cost_of_edge(edge_id)
        print(f"The cost of edge {edge_id} is {cost}.")

    def read_graph_from_file(self):
        """
        Read a graph from a file.

        This function prompts the user to enter the filename and reads the graph from that file.
        """
        filename = input("Please enter the filename: ")
        self.__controller.read_graph_from_file(filename)
        print("Graph read from file successfully!")

    def write_graph_to_file(self):
        """
        Write the graph to a file.

        This function prompts the user to enter the filename to which the graph will be written.
        """
        filename = input("Please enter the filename: ")
        self.__controller.write_graph_to_file(filename)
        print("Graph written to file successfully!")

    def generate_random_graph(self):
        """
        Generate a random graph.

        This function prompts the user to enter the number of vertices and edges for the random graph.
        """
        try:
            n, m = map(int, input("Please enter the number of vertices and edges: ").split())
        except ValueError:
            print("Invalid input! Please enter integers for the number of vertices and edges.")
            return

        self.__controller.generate_random_graph(n, m)
        print("Random graph generated successfully!")

    def bfs(self):
        try:
            x, y = input("Please enter the 2 vertices: ").split()
            x, y = int(x), int(y)
        except ValueError:
            print("Invalid input!")
            return
        if x >= self.__controller.graph.getter_for_vertices_counter() or y >= self.__controller.graph.getter_for_vertices_counter():
            print("The provided vertices MUST BE between 0 and n - 1. Try again!")
            return
        path = self.__controller.forward_bfs(x, y)
        if len(path) == 0:
            print("There is no path from " + str(x) + " to " + str(y))
        else:
            print("The length of the shortest path is " + str(len(path) - 1))
            print("The shortest path from " +
                  str(x) + " to " + str(y) + " is: ")
            print(path)

    def ui_hamiltonian_cycle(self):
        self.__controller.approximateTSPNearestNeighbour()
        hamPathVertices = self.__controller.graph.hamPathVertices
        if len(hamPathVertices) == 0:
            print("No cycle was found!")
        else:
            print("Hamiltonian path cost:", self.__controller.graph.hamPathCost)
            print("Edges:\n")
            for i in range(len(hamPathVertices) - 1, 0, -1):
                print(hamPathVertices[i], "->", hamPathVertices[i - 1], "")
            print(hamPathVertices[0], "->", hamPathVertices[-1], "\n")

    def ui_lowest_cost_walk(self):
        try:
            start_vertex, end_vertex = input("Please enter the start and end vertices: ").split()
            start_vertex, end_vertex = int(start_vertex), int(end_vertex)
        except ValueError:
            print("Invalid input! Please enter two integers separated by a space.")
            return

        if start_vertex >= self.__controller.graph.getter_for_vertices_counter() or end_vertex >= self.__controller.graph.getter_for_vertices_counter():
            print("The provided vertices must be between 0 and n - 1. Please try again.")
            return

        try:
            cost, path = self.__controller.lowest_cost_walk(start_vertex, end_vertex)
            if len(path) == 0:
                print("There is no path from {} to {}".format(start_vertex, end_vertex))
            else:
                print("The length of the lowest cost walk is:", cost)
                print("The lowest cost walk from {} to {} is:".format(start_vertex, end_vertex))
                print(path)
        except Exception as e:
            print("An error occurred:", e)

    def ui_prim_algorithm(self):
        start_vertex = int(input("Give the starting vertex: "))
        mst_edges = self.__controller.prim_algorithm(start_vertex)
        total_cost = 0
        print("The minimum spanning tree will have the edges: ")
        for start, end in mst_edges:
            print(f"{start} <-> {end}")
            total_cost += self.__controller.graph.getter_the_cost_of_edge_with_edges(start, end)
        print(f"The total cost of this MST is {total_cost}.")

    def print_menu(self):
        """
        Print the menu of the application.

        The user will choose an option from the menu.
        """
        menu = [
            "Retrieve the counts of vertices and edges",
            "Retrieve the graph's edges",
            "Retrieve the graph's vertices",
            "Retrieve the cost of a specified edge",
            "Retrieve the in-degree and out-degree of a specified vertex",
            "Retrieve the endpoints of a specified edge",
            "Determine if there is an edge from the first vertex to the second",
            "Modify an edge",
            "Add an edge",
            "Remove an edge",
            "Add a vertex",
            "Remove a vertex",
            "Copy the graph",
            "Read graph from file",
            "Write graph to file",
            "Generate a random graph",
            "Iterate through the set of inbound edges of a vertex",
            "Iterate through the set of outbound edges of a vertex",
            "Find the shortest path between 2 vertices, using a forward breadth-first search",
            "Find the lowest cost walk between the given vertices, using Bellman Ford's algorithm",
            "Get a minimum spanning tree (using Prim's Algorithm)",
            "Find a Hamilton cycle of low cost(approximate TSP)",
            "Exit"
        ]

        print("\nMenu:")
        for idx, option in enumerate(menu, start=1):
            print(f"{idx}. {option}")

    def run(self):
        """
        Main function that performs all the jobs
        """
        print("Welcome to the graph application!")
        while True:
            self.print_menu()
            command = input("Please enter a command: ")
            if command == "1":
                print("The number of vertices is: " + str(self.__controller.graph.getter_for_vertices_counter()))
                print("The number of edges is: " + str(self.__controller.graph.getter_number_of_edges()))
            elif command == "2":
                self.print_graph()
            elif command == "3":
                self.print_vertices()
            elif command == "4":
                self.print_the_cost()
            elif command == "5":
                self.get_in_degree_and_out_degree()
            elif command == "6":
                self.getter_of_the_extremities_of_edge()
            elif command == "7":
                self.check_if_edge_exists()
            elif command == "8":
                self.modify_cost_of_edge()
            elif command == "9":
                self.add_edge()
            elif command == "10":
                self.remove_edge()
            elif command == "11":
                self.add_vertex()
            elif command == "12":
                self.remove_vertex()
            elif command == "13":
                self.copy_graph()
            elif command == "14":
                self.read_graph_from_file()
            elif command == "15":
                self.write_graph_to_file()
            elif command == "16":
                self.generate_random_graph()
            elif command == "17":
                self.parse_inbound_edges()
            elif command == "18":
                self.parse_outbound_edges()
            elif command == "19":
                self.bfs()
            elif command == "20":
                self.ui_lowest_cost_walk()
            elif command == "21":
                self.ui_prim_algorithm()
            elif command == "22":
                self.ui_hamiltonian_cycle()
            elif command == "23":
                filename = "graph" + str(self.__controller.graph.getter_for_vertices_counter()) + "_modif.txt"
                self.__controller.write_graph_to_file(filename)
                print("Goodbye!")
                return
            else:
                print("Invalid command!. Please try again!")
