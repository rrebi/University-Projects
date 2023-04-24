import copy

from graph import Graph
import graph_functions


class UI:

    def __init__(self):
        pass

    @staticmethod
    def print_menu():
        print("1. Get the number of vertices.")
        print("2. Parse the set of vertices.")
        print("3. Check if there is an edge between 2 vertices.")
        print("4. The in and out degree of a vertex.")
        print("5. Parse the outbound edges of a vertex.")
        print("6. Parse the inbound edges of a vertex.")
        print("7. Modify the information about an edge.")
        print("8. Retrieve the information about an edge.")
        print("9. Copy the graph.")
        print("10. Write the graph into a text file.")
        print("11. Read the graph from a text file.")
        print("12. Add vertex.")
        print("13. Delete vertex.")
        print("14. Delete edge.")
        print("15/16. Graph from input1/input2.")
        print("17. Graph random.")
        print("18. Lowest path, BFS (Breadth First Search).")
        print("0. Exit.")

    def start(self):

        g = graph_functions.create_random_graph(10,20)

        self.print_menu()

        x=input()
        while (x!="0"):
            if x=="1":
                print(g.nr_of_vertices())
                graph_functions.print_graph(g)
            elif x=="2":
                print(g.parse_vertices())

            elif x=="3":
                vertex1 = int(input("Vertex1: "))
                vertex2 = int(input("Vertex2: "))
                print(g.is_edge(vertex1,vertex2))

            elif x=="4":
                vertex=int(input("Vertex: "))
                print("The out degree of the vertex is: ",len(g.parse_nin(vertex)))
                print("The in degree of the vertex is: ",len(g.parse_nout(vertex)))

            elif x=="5":
                vertex=int(input("Vertex: "))
                print(g.parse_nout(vertex))
            elif x=="6":
                vertex = int(input("Vertex: "))
                print(g.parse_nin(vertex))
            elif x=="7":
                vertex1 = int(input("Vertex1: "))
                vertex2 = int(input("Vertex2: "))
                value = int(input("New value: "))
                g.modify_value(vertex1,vertex2,value)
            elif x=="8":
                vertex1 = int(input("Vertex1: "))
                vertex2 = int(input("Vertex2: "))
                print(g.retrieve_value(vertex1,vertex2))
            elif x=="9":
                new_g=g.copy_graph()

            elif x=="10":
                g.into_file("output.txt")
            elif x=="11":
                g=g.from_file("output.txt")
            elif x=="12":
                v=input("New vertex: ")
                g.add_vertex(v)
            elif x=="13":
                v=input("Vertex to be deleted: ")
                g.remove_vertex(v)
            elif x=="14":
                v1,v2=input("Edge to be deleted: ")
                g.delete_edge(v1,v2)
            elif x=="15":
                g=g.from_file("input1.txt")
            elif x=="16":
                g=g.from_file("input2.txt")
            elif x == "17":
                g = graph_functions.create_random_graph(10, 20)
            elif x == "18":
                vertex1 = int(input("Vertex1: "))
                vertex2 = int(input("Vertex2: "))
                list = g.shortest_path(vertex1, vertex2)
                print(list)
            self.print_menu()
            x=input()


        return

ui=UI()
ui.start()
