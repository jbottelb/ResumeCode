#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/30/20 '''

'''
Graph is a dictionary of the node connnections
Max flow algorithm done with pseudocode of the Edmonds Karp algortihm,
found at https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
'''

import os, sys
from collections import defaultdict

def main():
    number = 1

    while (line := int(sys.stdin.readline().split()[0])):
        graph, source, target = build_graph()
        bandwidth = max_flow(graph, source, target)

        print("Network", str(number) + ':', "Bandwidth is", str(bandwidth) + ".")
        number += 1


def build_graph():
    '''
    Read graph with weights for edges
    '''
    graph = defaultdict(dict)

    # interpret input lines as nodes
    source, target, connections = map(int, sys.stdin.readline().split())

    for _ in range(connections):
        node1, node2, cap   = map(int, sys.stdin.readline().split())
        graph[node1][node2] = cap + graph[node1].get(node2, 0)
        graph[node2][node1] = cap + graph[node2].get(node1, 0)

    return graph, source, target


def BFS(graph, source, target):
    frontier = [[source]]
    visited = []

    while frontier:
        path = frontier.pop(0)
        node = path[-1]

        if node in visited:
            continue

        for neighbor in graph[node]:
            if graph[node][neighbor] != 0:
                curr_path = list(path)
                curr_path.append(neighbor)

                frontier.append(curr_path)

                if neighbor == target:
                    return True, curr_path

                visited.append(node)

    return False, []


def max_flow(graph, source, target):
    ''' Implementation of Edmonds Karp '''
    max = 0

    connects, path = BFS(graph, source, target)

    while connects:
        best = float('inf')

        for x in range(len(path) - 1):
            node1 = path[x]
            node2 = path[x + 1]

            if graph[node1][node2] < best:
                best = graph[node1][node2]

        max += best

        for x in range(len(path) - 1):
            node1 = path[x]
            node2 = path[x + 1]

            graph[node1][node2] -= best
            graph[node2][node1] -= best

        connects, path = BFS(graph, source, target)

    return max

if __name__ == '__main__':
    main()
