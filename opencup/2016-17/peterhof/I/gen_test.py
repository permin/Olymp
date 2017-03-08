#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    n = int(sys.argv[2])
    m = int(sys.argv[3])
    print n, m
    for _ in range(m):
        print random.randint(1, n),
        print random.randint(1, n)


main()
