#!/usr/bin/env python3

''' Created by Josh Bottelberghe Jul 31, 2020 '''

import os, sys

def main():

    m       = []
    input   = [ l.strip() for l in sys.stdin ]

    n = input[0]
    i = 1

    while int(n) != 0:
        for j in range(int(n)):
            m.append(input[i].split())
            i = i + 1

        print(output(rotate(m, int(n))), end='')



        m = []
        n = input[i]
        if int(n) != 0:

            print()

        i = i + 1

def rotate(m, size):
    """
    Rotates a square matrix 90 degrees clockwise
    """
    for i in range(size):
        for j in range(i, size):
            m[i][j], m[j][i] = m[j][i], m[i][j]

    for i in m:
        i.reverse()

    return m

def output(m):
    o = ''

    for r in m:
        for c in r:
            o = o + c + ' '
        o = o.strip() # o[:len(o) - 1]          # fence post
        o = o + '\n'

    return o


if __name__ == "__main__":
    main()
