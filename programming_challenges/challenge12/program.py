#!/usr/bin/env python3

''' Created by Josh Bottelberghe 9-25-20 '''

'''
This problem is solved by dynamic programmaing
and backtracking to get the route
Much of this code was developed by the model of the in
class problem, and much code is therefore similar
'''

import os, sys
from math import inf


def main():
    while True:
        line = int(sys.stdin.readline())

        # go unless it is the sentinal
        if line > 0:
            compute_and_print(line)
        else:
            break


def get_matrix(size):
    '''
    populates a matrix to use
    '''
    matrix = [[inf for _ in range(size + 1)]]

    for _ in range(size):
        matrix.append([inf] + list(map(int, sys.stdin.readline().split())))

    return matrix


def min_route(matrix, size):
    '''
    Compute the optimal path
    '''
    table = [[0] + [inf for _ in range(size)]]

    for _ in range(size):
        table.append([inf] + [0] * size)

    for row in range(1, size + 1):
        for col in range(1, size + 1):
            table[row][col] = matrix[row][col] + min(
                table[row    ][col - 1],
                table[row - 1][col    ],
                table[row - 1][col - 1]
            )

    return table


def find_path(matrix, n, table):
    '''
    Find the path we took
    '''
    path = []
    row, col = n, n

    while row > 0 and col > 0:
        path.append(matrix[row][col])

        if table[row][col] - matrix[row][col] == table[row][col - 1]:
            col -= 1
        elif table[row][col] - matrix[row][col] == table[row - 1][col]:
            row -= 1
        else:
            col -= 1
            row -= 1

    return reversed(path)


def compute_and_print(size):
    matrix = get_matrix(size)

    table = min_route(matrix, size)
    print(table[size][size])

    path = find_path(matrix, size, table)
    print(*path)   # dereferance iter


if __name__ == '__main__':
    main()
