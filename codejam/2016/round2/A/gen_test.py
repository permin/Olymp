#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    tests = int(sys.argv[2])
    n = int(sys.argv[3])
    print tests

    for _ in range(tests):
        print n,
        m = 2**n
        r = random.randint(0, m)
        p = random.randint(0, m - r)
        q = m - r - p
        assert p + q + r == (m)
        print r, p, q


main()
