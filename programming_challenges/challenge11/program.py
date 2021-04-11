#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-23-20 '''

'''
This problem is solved by dynamic programmaing
'''

import os, sys
# from math import sqrt (importing this is actually .01 slower)

# GLOBAL
Cashe = [0]         # stores all the values we have seen

def main():

    for line in sys.stdin:
        line = line.strip()

        print(least_perfect_square(int(line)))


def least_perfect_square(N):
    for i in range(len(Cashe), N+1): # only iterate to compute values we havent found
        values = []     # store possible routes

        for j in range(int(i**.5), 0, -1):
            values.append(Cashe[i - j**2])

        Cashe.append(1 + min(values))

    return Cashe[N]

if __name__ == "__main__":
    main()
