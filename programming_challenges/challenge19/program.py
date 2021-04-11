#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/30/20 '''

import os, sys
from collections import defaultdict


def main():
    for line in sys.stdin:
        line = line.strip().split()

        num = line[0]
        graph = build_graph()

        start = list(sorted(graph.keys()))[0]
        path = search_for_circut(graph, start, start, set([start]), [start], int(num))

        if path:
            print(*path, sep=' ')
        else:
            print('None')


def build_graph():
    '''
    Build graph out of dictionaries of edges
    '''
    graph = defaultdict(dict)

    for edge, line in enumerate(sys.stdin):
        line = line.strip().split()

        if '%' in line:
            break

        graph [int(line[0])] [int(line[1])] = edge
        graph [int(line[1])] [int(line[0])] = edge

    return graph


def search_for_circut(graph, start, vertex, visited, path, size):
    '''
    Recursive
    Uses circut method from class to search paths
    '''
    # base case (we have made it back to the start)
    if len(path) == size:
        if start in graph[vertex]:
            path.append(start)
            return path
        else:
            return

    # recursive step, move forward in graph
    for neighbor in sorted(graph[vertex]):
        if neighbor not in visited:
            visited.add(neighbor)
            path.append(neighbor)

            if search_for_circut(graph, start, neighbor, visited, path, size):
                return path

            visited.remove(neighbor)
            path.pop(-1)


if __name__ == '__main__':
    main()
