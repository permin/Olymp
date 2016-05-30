#!/usr/bin/python

import random
import sys


def main():
    n = sys.argv[1]
    n = int(n)
    print n
    for i in range(1, n):
        print i + 1, random.randint(1, i)
    for i in range(1, n):
        print i + 1, random.randint(1, i)

main()
