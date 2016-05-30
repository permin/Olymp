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
        print n,
        k = 1
        while k % 2 == 1:
            k = random.randint(1, n + 1)
        k = n
        if k % 2 == 1:
            k -= 1
        print k
        for _ in range(n):
            print random.random(),
        print


main()
