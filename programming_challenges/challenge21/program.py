#!/usr/bin/env python3
''' Created by Josh Bottelberghe 11/05/20 '''

import sys
from math import gcd


def main():
    for line in sys.stdin:
        if is_c_num(int(line.strip())):
            print('The number', line.strip(), 'is a Carmichael number.')
        else:
            print(line.strip(), 'is normal.')


def is_c_num(n):
    '''
    Finds if a number is a carmicheal number by application of the inverse
    of fermat's therom
    '''
    # 9 is the only special case
    if n == 9:
        return False

    for i in range(2, n):
        if gcd(i, n) != 1 and pow(i, n - 1, n) != 1:
            return True

    return False


if __name__ == '__main__':
    main()
