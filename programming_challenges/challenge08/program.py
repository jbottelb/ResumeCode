#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-9-20 '''

'''
Approach: Create a dictionary with each numbers moves and appropriatly
create permuatations
Note: the number 5 has no friends
'''

import os, sys
from itertools import permutations

moves = {'1': '68', '2': '79', '3': '48',
            '4': '390', '5': '', '6': '170',
            '7': '26', '8': '13', '9': '24',
            '0': '46'}

def main():
    all_paths = []

    for line in sys.stdin:
        line = line.strip().split()

        all_paths.append(sorted(gallop(line[0], int(line[1]) - 1, line[0])))

    print(output(all_paths))


def output(all_paths):
    ''' Handles proper output from list of lists of paths '''
    out = ''
    for paths in all_paths:
        for path in paths:
            out += path + '\n'
        out += '\n'

    return out[:len(out)-2]


def gallop(start, hops, route):
    poss = []
    if hops == 0:
        return route

    for move in moves[start]:
        # if we always extend, it will break down the string too
        if hops == 1:
            poss.append(gallop(move, hops-1, route + move))
        else:
            poss.extend(gallop(move, hops-1, route + move))

    return poss


if __name__ == "__main__":
    main()
