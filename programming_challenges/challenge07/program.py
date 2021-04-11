#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-2-20 '''

import os, sys
from itertools import permutations

def main():
    # create all panditial numbers (excluding the ones that don't divde well)
    pandigital = populate()
    fence_built = False

    for line in sys.stdin:
        line = line.strip()

        if line == '0':
            return

        # extra line between values, but not after the last
        if fence_built:
            print()
        else:
            fence_built = True

        ans = find_quo(pandigital, int(line))
        if len(ans) > 0:
            for a in ans: print(a[:5], '/', a[5:], '=', line)
        else:
            print("There are no solutions for", line, end="")
            print('.')


def find_quo(pandigital, N):
    possible = []
    for e in pandigital:
        if int(''.join(map(str,e[:5]))) / int(''.join(map(str,e[5:]))) == N:
            possible.append(''.join(map(str,e)))

    return possible


def populate():
    # create possibilites and prune
    population = []
    for p in permutations('0123456789'):
        p = ''.join(p)

        if int(p[:5]) % int(p[5:]) == 0:    # we only care about integer answers
            population.append(p)

    return population


if __name__ == "__main__":
    main()
