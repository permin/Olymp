#!/usr/bin/python

import random
import sys
from functions import *

print 1
n = 1000
print n

for i in range(n):
    M = 10**9
    print random.randint(-M, M),
    print random.randint(-M, M)

#outS(SequenceGenerator(Random(-11,23), 2)())

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(RandomString(AZ, 4), 20)())
