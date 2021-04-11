#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-2-20 '''

import os, sys

def main():
    for line in sys.stdin:
        line = line.strip().split()
        val = longest_distinct_set(line)
        output(val[0], val[1])


def longest_distinct_set(line):
    '''
    Returns the longest distinct set in O(n) time by storing seen values in a map
    uses sliding wondow approach with use of a start and end pointer
    '''
    passed = {}
    max_len = 0
    start_pointer = 0
    max_set = []

    for end_pointer in range(len(line)):
        if line[end_pointer] in passed:
            start_pointer = max(start_pointer, passed[line[end_pointer]] + 1)

        # moves index stored where value was last passed
        passed[line[end_pointer]] = end_pointer

        # update if new longest
        if max_len < end_pointer - start_pointer + 1:
            max_len = end_pointer - start_pointer + 1
            max_set = line[start_pointer:end_pointer+1]

    return max_len, max_set


def output(i, line):
    '''
    converts set to appropriate string output
    '''
    output = str(i) + ': '
    for l in line:
        output += l + ", "
    print(output[:len(output)-2])


if __name__ == "__main__":
    main()
