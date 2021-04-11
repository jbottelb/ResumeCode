#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-16-20 '''

'''
Approach: use itertools combintaion and python string manipulation
to generate all possible combos
'''

import os, sys
from itertools import combinations

def main():
    answers = []

    for line in sys.stdin:
        line = line.strip().split()

        answers.append(gen(int(line[0]), int(line[1])))

    print(output(answers))


def output(ans):
    out = ''

    for test in ans:
        for line in test:
            out += ''.join(line) + '\n'
        out += '\n'

    return out[:len(out)-2]

def gen(size, ones):
    '''
    Give all indices of the ones, then create the bit strings
    with 1's at those indices
    '''
    poss = []

    for indices in combinations(range(size), ones):
        template = ['0'] * size

        for i in indices:
            template[i] = '1'

        poss.append(''.join(template))

    return poss[::-1]  # must be reversed to match output


if __name__ == "__main__":
    main()
