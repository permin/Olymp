#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    n = int(sys.argv[2])
    q = int(sys.argv[3])
    print n, q
    print(''.join([random.choice("xza") for _ in range(n)]))
    for _ in range(q):
        print random.randint(1, n * 10)


main()
