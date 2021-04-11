#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/24/20 '''

'''
Does a Topological sort. Code written with help of class examples
'''

import os, sys, heapq
import collections

# Graph representation
Graph = collections.namedtuple('Graph', 'edges degrees')

def main():
    graph = build_graph()
    vertices = top_sort(graph)

    print(''.join(vertices))


def build_graph():
    ''' Builds the graph '''
    edges   = collections.defaultdict(set)
    degrees = collections.defaultdict(int)

    for line in sys.stdin:
        for n in range(len(line.strip()) - 1):
            if not line[n + 1] in edges[line[n]]:
                edges[line[n]].add(line[n + 1])
                degrees[line[n + 1]] += 1
                degrees[line[n]]

    return Graph(edges, degrees)


def top_sort(graph):
    ''' does a topological sort on the graph '''
    frontier = [v for v, d in graph.degrees.items() if d == 0]
    visited  = []

    while frontier:
        vertex = frontier.pop()
        visited.append(vertex)

        for neighbor in graph.edges[vertex]:
            graph.degrees[neighbor] -= 1
            if graph.degrees[neighbor] == 0:
                frontier.append(neighbor)

    return visited


if __name__ == '__main__':
    main()
