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
    for _ in range(n):
        print random.randint(1, 1000 * 10)


main()
