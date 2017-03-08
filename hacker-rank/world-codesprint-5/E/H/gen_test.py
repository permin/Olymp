#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    t = int(sys.argv[2])
    n = int(sys.argv[3])
    print t
    for _ in range(t):
        print n
        for i in range(n):
            print random.randint(1, 10**9),
        print
        for i in range(1, n):
            print i + 1, 1 + random.randint(0, i - 1)

main()
