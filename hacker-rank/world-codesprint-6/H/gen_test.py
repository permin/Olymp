#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    n = int(sys.argv[2])
    k = int(sys.argv[3])
    print n, k
    for _ in range(n):
        print random.randint(0, 20),
        print random.randint(0, 20)


main()
