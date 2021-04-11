#!/usr/bin/env python3
''' Created by Josh Bottelberghe 11/05/20 '''

import sys


def main():
    for line in sys.stdin:
        print(calculate(line.strip().split()))


def calculate(line):
    '''
    simplifies parenthesis that do not also contain parentesis into integer
    solutions... until only one remains
    '''
    exp = []
    for e in line:
        for i in e:
            exp.append(i)

    while ')' in exp:
        end, start = 0, 0

        for i in range(len(exp)):
            if exp[i] == '(':
                start = i
            if exp[i] == ')':
                end = i
                break

        if start+1 == end-1:
            # deal with the single numbers in parentesis
            exp.pop(start)
            exp.pop(end-1)
        else:
            # Compute and replace sections
            n = simplify(exp[start+1:end])
            exp = exp[:start] + [n] + exp[end+1:]

    return exp[0]


def simplify(sub):
    '''
    I sincerely apologize for how absolutley attrocious this function looks.
    I tried to work out how to pass an operator to a function and failed
    It is suppose to take a subsection of valid parentesis and operate

    The function takes a simplified operation in the form ['op', 'int', ...]
    and returns the integer it should be to replace it in the experession
    '''
    n = None

    if sub[0] == '+':
        sum = 0
        for i in sub[1:]:
            try:
                sum += int(i)
            except TypeError:
                return False
        return int(sum)
    if sub[0] == '-':
        sum = int(sub[1])
        for i in sub[2:]:
            try:
                sum -= int(i)
            except TypeError:
                return False
        return int(sum)

    if sub[0] == '*':
        sum = 1
        for i in sub[1:]:
            try:
                sum *= int(i)
            except TypeError:
                return False
        return int(sum)
    if sub[0] == '/':
        sum = int(sub[1])
        for i in sub[2:]:
            try:
                sum /= int(i)
            except TypeError:
                return False
        return int(sum)
    if not n:
        return False
    else:
        return int(n)


if __name__ == '__main__':
    main()
