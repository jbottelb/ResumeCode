#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-16-20 '''

'''
This problem is solved with a greedy algorithm
'''

import os, sys

def main():
    
    for line in sys.stdin:
        line = line.strip().split()

        print(build(line))


def build(bricks):
    # take care of 4s
    rows   = int(bricks[3])
    ones   = int(bricks[0])
    twos   = int(bricks[1])
    threes = int(bricks[2])

    # take care of 3
    while threes > 0:
        if ones > 0:
            ones -= 1
        threes -= 1
        rows += 1

    # and 2's
    while twos > 0:
        twos -= 1
        if twos > 0:
            twos -= 1
        elif ones > 0:
            ones -= 2   # ones can go negative
        rows += 1

    # and 1's
    while ones > 0:
        ones -= 4
        rows += 1

    return rows

if __name__ == "__main__":
    main()
