#!/usr/bin/env python3

import concurrent.futures
import os
import requests
import sys
import time

# Functions

def usage(status=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-h HAMMERS -t THROWS] URL
    -h  HAMMERS     Number of hammers to utilize (1)
    -t  THROWS      Number of throws per hammer  (1)
    -v              Display verbose output
    ''')
    sys.exit(status)

def hammer(url, throws, verbose, hid):
    ''' Hammer specified url by making multiple throws (ie. HTTP requests).

    - url:      URL to request
    - throws:   How many times to make the request
    - verbose:  Whether or not to display the text of the response
    - hid:      Unique hammer identifier

    Return the average elapsed time of all the throws.
    '''

    for throw in range(throws):
        start = time.time()
        # make request
        response = requests.get(url)

        if (verbose):
            print(response.text)

        print('Hammer: ', hid, 'Throw: ', throw, 'Elapsed time: ', f'{(time.time() - start):.4f}')

    return (time.time() - start) / throws

def do_hammer(args):
    ''' Use args tuple to call `hammer` '''
    return hammer(*args)

def main():
    hammers = 1
    throws  = 1
    verbose = False
    URL     = ''

    if len(sys.argv) == 1:
        usage(1)

    # Parse command line arguments
    for i, arg in enumerate(sys.argv):
        if arg == '-v':
            verbose = True
        elif arg == '-h':
            try:
                hammers = int(sys.argv[i + 1])
            except (IndexError, ValueError):
                usage(1)
        elif arg == '-t':
            try:
                throws = int(sys.argv[i + 1])
            except (IndexError, ValueError):
                usage(1)

    # The last argument should be the url, and start with an h
    if sys.argv[-1][0] != 'h':
        usage(1)
    else:
        URL = sys.argv[-1]

    # Create pool of workers and perform throws
    hammer_args = [(URL, throws, verbose, hid) for hid in range(hammers)]

    time = 0
    with concurrent.futures.ProcessPoolExecutor() as executor:
        for hid, t in zip(range(hammers), executor.map(do_hammer, hammer_args )):
            time += t
            print('Hammer: ', hid, 'AVERAGE , Elapsed Time: ', f'{t:.4f}')


    print('TOTAL AVERAGE ELAPSED TIME: ', f'{(time / throws * hammers):.4f}')

# Main execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
