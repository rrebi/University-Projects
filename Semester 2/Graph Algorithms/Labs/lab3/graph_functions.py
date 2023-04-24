import time
import random
from graph import Graph

def print_graph(g):
    print("Outbound neighborss:")
    for x in g.parse_vertices():
        s = str(x) + ":"
        for y in g.parse_nout(x):
            s = s + " " + str(y)
        print(s)
    print("Inbound neighborss:")
    for x in g.parse_vertices():
        s = str(x) + ":"
        for y in g.parse_nin(x):
            s = s + " " + str(y)
        print(s)


def parse_graph(g):
    print("Parsing outbound neighborss:")
    start = time.time()
    for x in g.parse_vertices():
        for y in g.parse_nout(x):
            pass
    print("Finished in %sms" % (1000 * (time.time() - start)), )
    print("Parsing inbound neighborss:")
    start = time.time()
    for x in g.parse_vertices():
        for y in g.parse_nin(x):
            pass
    print("Finished in %sms" % (1000 * (time.time() - start)), )


def create_random_graph(n, m):
    g = Graph(n)
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if not g.is_edge(x, y):
            g.add_edge(x, y)
            g.add_edge(y, x)
            m = m - 1

    return g;

def create_random_graph_with_costs():
    g=Graph(10)

    cost = {
        (0, 1): 3,
        (0, 2): 6,
        (1, 2): 2,
        (1, 3): 2,
        (3, 2): 2,
        (2, 4): 10,
    }
    for edge in cost.keys():
        g.add_edge(edge[0], edge[1])
    return g, cost

