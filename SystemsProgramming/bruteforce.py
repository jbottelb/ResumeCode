#!/usr/bin/env python3

import concurrent.futures
import hashlib
import os
import string
import sys

# Constants

ALPHABET = string.ascii_lowercase + string.digits

# Functions

def usage(exit_code=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-a ALPHABET -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file''')
    sys.exit(exit_code)

def md5sum(s):
    ''' Compute md5 digest for given string. '''
    msum = hashlib.md5(s.encode())
    return msum.hexdigest()

def permutations(length, alphabet=ALPHABET):
    ''' Recursively yield all permutations of the given length using the
    provided alphabet. '''

    if length == 0:
        yield ''
    else:
        for letter in alphabet:
            for x in permutations(length - 1, alphabet):
                yield letter + x

def flatten(sequence):
    ''' Flatten sequence of iterators. '''
    for it in sequence:
        for x in it:
            yield x

def crack(hashes, length, alphabet=ALPHABET, prefix=''):
    ''' Return all password permutations of specified length that are in hashes
    by sequentially trying all permutations. '''
    return [prefix + perm for perm in permutations(length, alphabet) if md5sum(prefix + perm) in hashes]

def cracker(arguments):
    ''' Call the crack function with the specified arguments '''
    return crack(*arguments)

def smash(hashes, length, alphabet=ALPHABET, prefix='', cores=1):
    ''' Return all password permutations of specified length that are in hashes
    by concurrently subsets of permutations concurrently.
    '''
    args = ((hashes, length-1, alphabet, prefix + letter) for letter in alphabet)

    with concurrent.futures.ProcessPoolExecutor(cores) as executor:
        passwords = flatten(executor.map(cracker, args))


    return passwords

def main():
    arguments   = sys.argv[1:]
    alphabet    = ALPHABET
    cores       = 1
    hashes_path = 'hashes.txt'
    length      = 1
    prefix      = ''

    argInd = 1                   # this will be used to skip over flags
    for arg in arguments[::2]:
        if arg == '-h':
            usage(0)
        elif arg == '-a':
            alphabet = arguments[argInd]
        elif arg == '-c':
            cores = int(arguments[argInd])
        elif arg == '-l':
            length = int(arguments[argInd])
        elif arg == '-p':
            prefix = arguments[argInd]
        elif arg == '-s':
            hashes_path = arguments[argInd]
        else:
            usage(1)
        argInd += 2

    hashes = set()
    hashTot = open(hashes_path)
    
    for hash in hashTot:
        hashes.add(hash.strip())

    if length == 1 or cores == 1:
        result = crack(hashes, length, alphabet, prefix)
    else:
        result = smash(hashes, length, alphabet, prefix, cores)

    for password in result:
       print(password)


# Main Execution

if __name__ == '__main__':
    main()
