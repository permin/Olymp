#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    n = int(sys.argv[2])
    print n
    d = 0
    a = 1000 * 1000
    for _ in range(n):
        if d == 0:
            print '+', random.randint(0, a)
            d += 1
        else:
            if random.randint(0, 1) == 0:
                print '+', random.randint(0, a)
                d += 1
            else:
                print '-'
                d -= 1

main()
