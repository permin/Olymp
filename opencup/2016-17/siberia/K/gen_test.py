#!/usr/bin/python

import random
import sys


def main():
    # TODO don't remove!
    seed = int(sys.argv[1])
    random.seed(seed)

    # TODO test generation

    n = int(sys.argv[2])
    print(''.join([random.choice("0123456789") for _ in range(n)]))

    q = 100
    p = random.choice([11, 13, 17, 19, 23, 1000 * 1000 *
                       1000 + 7, 1000 * 1000 * 1000 + 9])
    print q, p
    for _ in range(q):
        print random.randint(0, p - 1)


main()
