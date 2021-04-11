#!/usr/bin/env python3

''' Created by Josh Bottelberghe 10-08-20 '''

'''
Reads a sorted list of integers and makes it a BST
'''

import sys


def main():
    for line in sys.stdin:
        root = grow_tree(line.strip().split())
        print_tree(root)


class Node:
    ''' Binary tree Node '''
    def __init__(self, value):
        self.value = value
        self.left  = None
        self.right = None


def print_tree(root):
    output = ''
    q = []
    q.append(root)

    while q:
        level = len(q)
        while level > 0:
            n = q.pop(0)
            output += n.value + ' '

            if n.left:  q.append(n.left)
            if n.right: q.append(n.right)
            level -= 1
        output = output[:len(output)-1]
        output += '\n'

    print(output[:len(output)-1])


def grow_tree(nums):
    if not nums:
        return None

    mid  = (len(nums)) // 2
    root = Node(nums[mid])

    root.left  = grow_tree(nums[:mid])
    root.right = grow_tree(nums[mid+1:])

    return root

if __name__ == '__main__':
    main()
