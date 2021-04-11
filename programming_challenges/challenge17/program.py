#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/21/20 '''

'''
Find minimum distance between points
'''

import os, sys, heapq
from collections import defaultdict

def main():
    '''read number of lines, then build the graph with that many lines'''
    lines = int(sys.stdin.readline())

    while lines != 0:
        graph = read_graph(lines)
        mst   = compute_mst(graph)

        distance = sum(graph[s][t] for s, t in mst.items() if s != t)

        print(f'{distance:.2f}')

        lines = int(sys.stdin.readline())


def compute_mst(graph):
    '''compute MST (adapted from lecture code)'''
    frontier = []
    visited   = {}
    start    = list(graph.keys())[0]

    heapq.heappush(frontier, (0, start, start))

    while frontier:
        weight, source, target = heapq.heappop(frontier)

        if target not in visited:
            visited[target] = source

            for n, d in graph[target].items():
                heapq.heappush(frontier, (d, target, n))

    return visited


def read_graph(lines):
    ''' Create grapth with distance as edges '''
    graph = defaultdict(dict)

    for _ in range(lines):
        line = sys.stdin.readline()
        x, y = line.split()
        graph[(x, y)]

    for source in graph.keys():
        for target in graph.keys():
            if source != target: # dont want distance to itself
                # calculate distance and make it the edge
                x1, y1 = source
                x2, y2 = target

                dist = (((float(x2)-float(x1))**2 + (float(y2)-float(y1))**2))**.5
                graph[source][target] = dist
                graph[target][source] = dist
    return graph


if __name__ == "__main__":
    main()
