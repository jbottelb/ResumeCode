
#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10/16/20 '''

import sys, os
from collections import defaultdict

def main():
   input = [line.strip().split() for line in sys.stdin.readlines()]
   i = 0
   des = input[i]

   while int(des[0]) != 0 and int(des[1]) != 0:
       connected = defaultdict(set)

       longest_road = 0
       i += 1


       for _ in range(int(des[1])):
           connected[int(input[i][0])].add(int(input[i][1]))
           connected[int(input[i][1])].add(int(input[i][0]))
           i += 1

       for node in connected:
           visited = set()
           roads = []
           new_longest_road = find_longest_road(connected, node, visited, 0, roads, [node, None, None])
           longest_road = max(longest_road, new_longest_road)

       print(longest_road)
       des = input[i]

def find_longest_road(graph, vertex, visited, path, lengths, checked):
   if (vertex, checked[1]) in visited or (checked[1], vertex) in visited:
       return path - 1

   visited.add( (vertex, checked[1]) )

   for edge in graph[vertex]:
       lengths.append(find_longest_road(graph, edge, visited, path + 1, lengths, [edge, checked[0], checked[1]]))

   return max(lengths)


if __name__ == '__main__':
   main()
