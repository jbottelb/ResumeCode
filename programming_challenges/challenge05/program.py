#!/usr/bin/env python3

''' Created by Josh Bottelberghe Aug 20, 2020'''

import sys

def main():
    known = {}   # (number: cycles to get to 1) used to save calculating known values

    for line in sys.stdin:
        line = line.strip().split()
        known, out = colatz_max(known, int(line[0]), int(line[1]))
        print(line[0], line[1], out[0], out[1])


def colatz_max(known, low, high):
    ''' Finds highest colatz cycle '''
    max = low, 1

    # in case someone is to not know that 1000000 is greater than 1
    if low > high:
        low, high = high, low

    for i in range(low, high+1):
        known, temp = colatz_num(known, i)

        known[i] = temp

        if temp > max[1]:
            max = i, temp

    return known, max

def colatz_num(known, n):
    ''' Counts colatz passes '''
    i = 0

    while n != 1:
        if n in known:
            return known, i + known[n]
            # print(n, i, known[n])
        if n % 2 == 1:
             n = 3 * n + 1
        else:
            n = n / 2
        i += 1

    return known, i + 1 # include the 1

if __name__ == "__main__":
    main()
