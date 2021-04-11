#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10-09-20 '''

'''
Approach: use a modified sliding window to find valid paths by moving through
binary tree
'''

import sys

def main():
    for line in sys.stdin:
        line = line.strip().split()

        bin_target = str(bin(int(line[0])))[2:]

        root      = create_bst(list(map(int, line[1])), 0)
        num_paths = walk(root, bin_target)

        print("Paths that form", str(line[0]), "in binary (" + str(bin_target) + "):", num_paths)


class Node:
    ''' Binary tree Node '''
    def __init__(self, value):
        self.value = value
        self.left  = None
        self.right = None


def create_bst(nums, i):
    if i > len(nums) - 1:
        return 0

    root = Node(nums[i])

    root.left  = create_bst(nums, 2*i + 1)
    root.right = create_bst(nums, 2*i + 2)

    return root


def walk(root, target):
    if not root:
        return 0

    num = path_find(root, target, len(target), 1)
    num += walk(root.left, target) + walk(root.right, target)
    return num

def path_find(root, target, l, depth):
    if not root or int(target[depth - 1]) != root.value:
        return 0

    if l > depth:
        num = path_find(root.left, target, l, depth+1)
        num += path_find(root.right, target, l, depth+1)
        return num

    if int(target[depth-1]) == root.value:
        return 1

    return 0


if __name__ == '__main__':
    main()
