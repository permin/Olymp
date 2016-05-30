#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation
    total_n = int(sys.argv[2])
    q = int(sys.argv[3])

    print q
    l = random.randint(1, total_n)
    print 'a' * l
    total_n -= l
    for _ in range(q):
        if total_n == 0:
            t = 2
        else:
            t = random.randint(1, 2)
        if t == 2:
            print t, random.randint(1,  10**5)
        elif t == 1:
            l = random.randint(1, total_n)
            print t, 'a' * l
            total_n -= l
        else:
            raise

main()
