#!/usr/bin/env python3
import sys
'''
Written by Josh Bottelberghe on Wed 19 Aug

Purpose:            Rank Value of cards in poker deck
General approach:   Give each number an integer value, and
                    each suit a small frational value
'''

def main():
        people = []
        left = None


        for line in sys.stdin:
            line = line.strip().split()

            if len(line) == 1:
                pass
            else:
                people.append(line)

        for person in people:
            person.append(convert_to_num(person[1], person[2]))

        people.sort(key = lambda tup: tup[3], reverse=True)

        out = ''
        for person in people:
            out += person[0] + ', '

        print(out[:len(out) - 2])   # remove fencepost

            if line == '0':
                return

            if not left or left == 0:
                left = int(line[0])
            elif left > 0:
                people.append(line)
                left = left - 1
                if left == 0:
                    print_order(people)
                    people = []



def print_order(people):
    for person in people:
        person.append(convert_to_num(person[1], person[2]))

    people.sort(key = lambda tup: tup[3], reverse=True)

    out = ''
    for person in people:
        out += person[0] + ', '

    print(out[:len(out) - 2])   # remove fencepost


def convert_to_num(rank, suit):
    ''' Converts a card value into a number '''
    value = 0

    if suit == 'C':
        value += .1
    elif suit == 'D':
        value += .2
    elif suit == 'H':
        value += .3
    elif suit == 'S':
        value += .4

    if rank == 'A':
        value += 14
    elif rank == 'K':
        value += 13
    elif rank == 'Q':
        value += 12
    elif rank == 'J':
        value += 11
    else:
        value += int(rank)

    return value

if __name__ == "__main__":
    main()
