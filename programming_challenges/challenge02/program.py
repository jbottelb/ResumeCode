#!/usr/bin/env python3
import sys
'''
Written by Josh Bottelberghe on thur Jul 23, 2020

Purpose:            Check validity of html tags in a string
General approach:   Tags are added to a stack, then popped when closed.
'''

def main():

    for l in sys.stdin:
        if check_balance(l):
            print('Balanced')
        else:
            print('Unbalanced')

def check_balance(str):
    '''
    There needs to be a stack, which adds the tags as it finds opening ones,
    then when it finds closing ones, it pops them.
    We need a 'pointer' which will act as our way of moving through the string
    '''

    pointer = 0     # this is the index of the string it is at
    stack   = []    # this is a stack which will have the tags added

    while pointer < len(str):
        if str[pointer] == '<':
            pointer += 1
            if str[pointer] == '/':
                pointer += 1
                tag, pointer = get_tag(str, pointer)

                if len(stack) == 0:
                    return False        # catches stack is empty and we cant close

                if not tag == stack.pop():
                    return False
            else:
                tag, pointer = get_tag(str, pointer)
                stack.append(tag)
        pointer += 1

    # has everything been closed?
    if len(stack) != 0:
        return False

    return True

def get_tag(str, pointer):
    '''
    takes a string and a pointer to return a tag, and the pointer after the tag
    '''
    tag = ''
    while str[pointer] != '>':
        tag = tag + str[pointer]
        pointer += 1
    return tag, pointer

if __name__ == "__main__":
    main()
