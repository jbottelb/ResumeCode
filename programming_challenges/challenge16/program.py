#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/16/20 '''

''' Use of Djikstra's algorithm '''

import sys, math, heapq
from collections import defaultdict


def main():
   rows, col = map(int, sys.stdin.readline().split())

   while rows != 0 or col != 0:
       input = []

       for _ in range(rows):
           input.extend(sys.stdin.readline().split())

       graph = build(input, rows, col)
       start = input.index('S')
       end = []

       for x in range(len(input)):
           if input[x] == 'E':
               end.append(x)

       path = min_path(graph, start)
       output(path, start, end)

       rows, col = map(int, sys.stdin.readline().split())


def output(path, start, ends):
   length = float('inf')
   final = start
   no_path = False

   for end in ends:
       if end in path:
           if path[end][1] < length:
               length = path[end][1]
               final = end
               no_path = True

   if not no_path:
       print('Cost: 0 Path: None')
   else:
       path = ' '.join([ str(a) for a in backtrack(path, start, final) ])
       print("Cost:", length, "Path:", path)


def build(arr, num_rows, num_cols):
   graph = defaultdict(dict)

   # ok this is pretty bad but it builds the graph
   for row in range(num_rows):
       for col in range(num_cols):
           id = (row * num_cols) + col
           element = arr[id]
           if element is not '1':
               for r in range(-1, 2):
                   if r + row >= 0 and r + row < num_rows:
                       for c in range(-1, 2):
                           if c + col >= 0 and c + col < num_cols:
                               num = ((r + row) * num_cols) + col + c
                               if not arr[num] == '1' and num != id:
                                   graph[id][num], graph[num][id] = abs(r) + abs(c), abs(r) + abs(c)

   return graph


def min_path(g, start):
   f = []
   visited  = {}

   heapq.heappush(f, (0, start, start))

   while f:
       weight, source, target = heapq.heappop(f)

       if target in visited:
           continue

       visited[target] = (source, weight)

       for neighbor, cost in g[target].items():
           heapq.heappush(f, (weight + cost, target, neighbor))

   return visited


def backtrack(visited, source, target):
   path = []
   curr = target

   while curr != source:
       path.append(curr)
       curr = visited[curr][0]

   path.append(source)
   return reversed(path)


if __name__ == '__main__':
   main()
