import copy
import time
import random
from queue import Queue

class Vertex:
    def __eq__(self, other):
        pass

    def __hash__(self):
        pass


class Graph:
    def __init__(self, n):
        self.vertices = dict()
        self.values = dict()
        self.values = {"vertex1": list(),
                       "vertex2": list(),
                        "value" : list()}
        for i in range(n):
            self.vertices[i] = (set(), set())


    def add_edge(self, x, y):

        self.values["vertex1"].append(x)
        self.values["vertex2"].append(y)
        self.values["value"].append(0)

        x=int(x)
        y=int(y)
        self.vertices[x][0].add(y)
        self.vertices[y][1].add(x)

    def add_vertex(self,v):
        self.vertices[self.nr_of_vertices()]=(set(), set())

    def remove_vertex(self,v):
        v=int(v)
        self.vertices.pop(v)
        for i in range(0,self.nr_of_edges()):
            if self.values["vertex1"][i]==v or self.values["vertex2"][i]==v:
                self.values["vertex1"].pop(i)
                self.values["vertex2"].pop(i)
                self.values["value"].pop(i)

    def delete_edge(self,v1,v2):
        for i in range (0,self.nr_of_edges()):
            if (self.values["vertex1"]==v1 and self.values["vertex2"]==v2):
                self.values["value"].pop(i)
                self.values["vertex1"].pop(i)
                self.values["vertex2"].pop(i)



    def is_edge(self, x, y):
        return (y in self.vertices[x][0])

    def parse_vertices(self):
        vertices_list = list()
        for key in self.vertices:
            vertices_list.append(key)
        return vertices_list

    def nr_of_edges(self):
        s=0

        for x in self.vertices:
            s+=len(self.parse_nout(x))
        return s

    def parse_nout(self, x):
        nout_vertices = list()
        for y in self.vertices[x][0]:
            nout_vertices.append(y)
        return nout_vertices


    def parse_nin(self, x):
        nin_vertices = list()
        for y in self.vertices[x][1]:
            nin_vertices.append(y)
        return nin_vertices

    def parse_nin1(self, x):
        nin_vertices = list()
        vertices = self.parse_vertices()
        for vertex in vertices:
            if x in self.vertices[vertex]:
                nin_vertices.append(vertex)
        return nin_vertices

    def nr_of_vertices(self):
        return len(self.vertices)

    def modify_value(self,x,y,value):
        x=int(x)
        y=int(y)
        for i in range(0,self.nr_of_edges()):
            if (self.values["vertex1"][i]==x and self.values["vertex2"][i]==y):
                self.values["value"][i]=value

    def retrieve_value(self,x,y):
        for a in range (len(self.values)):
            if (self.values["vertex1"][a]==x and self.values["vertex2"][a]==y):
                return self.values["value"][a]

    def copy_graph(self):
        n=self.nr_of_vertices()
        new_g = Graph(n)
        new_g = copy.deepcopy()
        return new_g


    def into_file(self,txt):
        file_name = txt
        open('output.txt', 'w').close()
        with open(file_name, "w") as f:

            f.write(str(self.nr_of_vertices()) + ', ' + str(self.nr_of_edges()) + '\n')
            for x in range(0, self.nr_of_edges()):
                f.write(str(self.values["vertex1"][x]) + ', ' + str(self.values["vertex2"][x]) + ', ' + str(self.values["value"][x]) + '\n')

    def from_file(self,txt):

        file_name = txt
        with open(file_name, "r") as f:
            line=f.readline()
            x,y=line.split(',')
            x=int(x)
            g=Graph(x)
            for line in f.readlines():
                line=line.strip()
                if line != '\n':
                    if len(line)>1:
                        x,y,value=line.split(maxsplit=2,sep=', ')
                        x=int(x)
                        y=int(y)
                        value=int(value)
                        g.add_edge(x,y)
                        g.modify_value(x,y,value)
        return g


    # Write a program that, given a directed graph and two vertices, finds a lowest length path between them,
    # by using breadth-first search from the starting vertex.
    def shortest_path(self, start_vertex, end_vertex):
        visited = {}
        level = {}
        parent = {}
        queue = Queue()

        for vertex in range(self.nr_of_vertices()):
            visited[vertex] = False
            parent[vertex] = None
            level[vertex] = -1

        visited[start_vertex] = True
        level[start_vertex] = 0
        queue.put(start_vertex)

        while not queue.empty():
            u = queue.get()
            visited[u] = True

            for neighbour in self.parse_nin(u):
                if not visited[neighbour]:
                    visited[neighbour] = True
                    parent[neighbour] = u
                    queue.put(neighbour)

        path = []
        while end_vertex is not None:
            path.append(end_vertex)
            end_vertex = parent[end_vertex]

        if len(path) > 0:
            return path[::-1]
        else:
            raise Exception("No path between {start_vertex} and {end_vertex}")

# def main1():
#     g = Graph(10)
#     g.add_edge(0, 3)
#     g.add_edge(0, 4)
#     g.add_edge(1, 2)
#
#     print(g.is_edge(0, 3))
#     print(g.is_edge(0, 2))
#     parse_graph(g)
#
#
# def main():
#     n = 10
#     g = create_random_graph(n, 10 * n)
#     print_graph(g)
#     parse_graph(g)


#main1()
