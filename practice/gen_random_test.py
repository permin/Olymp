#!/usr/bin/python

import random
import sys
from functions import *

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(Random(1,3), 20)())
#outS(SequenceGenerator(RandomString(AZ, 4), 20)())

n = 3
m = 5

print n, m, n/2
for _ in range(m):
    print Random(1, n)(),
    print Random(1, n)(),
    print random.choice(random.choice(
        [xrange(-10**15, -10**15 + 100000),
        xrange(10**15 - 100000, 10**15)]))
