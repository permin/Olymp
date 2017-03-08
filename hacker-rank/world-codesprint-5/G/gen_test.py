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

    max_weight = 10**6
    xs = sorted(random.randint(1, 10**6) for _ in range(n))
    ws = list(random.randint(1, max_weight) for _ in range(n))
    for (x, w) in zip(xs, ws):
        print x, w

main()
