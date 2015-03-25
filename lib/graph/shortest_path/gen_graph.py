#!/usr/bin/python

import sys
import random

n = int(sys.argv[1])
m = int(sys.argv[2])

print n, m, 1
for _ in xrange(m):
    print random.randint(1, n),
    print random.randint(1, n),
    print random.randint(-10**10 * 2, 10**12)
