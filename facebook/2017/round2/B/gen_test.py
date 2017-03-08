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
    t = 150
    print t
    M = 10000000
    for _ in range(t):
        num = random.randint(1, n)
        print num
        print random.randint(1, M),
        print random.randint(0, M),
        print random.randint(0, M),
        print random.randint(1, M)

        print random.randint(1, M),
        print random.randint(0, M),
        print random.randint(0, M),
        print random.randint(1, M)


main()
