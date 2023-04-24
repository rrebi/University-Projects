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
            m = m - 1
    return g