#!/usr/bin/env python3
from collections import defaultdict
import sys

def main():
    for l in sys.stdin:
        l = l.strip().split(' ')                # remove endline and seperate words by space
        print(rip(l[0], l[1]))

def rip(w1, w2):
    '''
    Rips the letters from each word to see how many w2s can be made from w1
    Max at 99999999 words
    '''
    letters1 = defaultdict(int)  # default is 0
    letters2 = defaultdict(int)  # default is 0

    for c in w1:
        letters1[c] += 1

    for c in w2:
        letters2[c] += 1

    max = 99999999
    for c in letters2:
        n = letters1[c] // letters2[c]
        if n < max:
            max = n
    return max


if __name__ == "__main__":
    main()
