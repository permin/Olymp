#!/usr/bin/python

import random
import sys
from functions import *

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(Random(1,3), 20)())
#outS(SequenceGenerator(RandomString(AZ, 4), 20)())
t = 10
print t
for i in range(t):
    n = 100*1000
    outS(shuffle(list(range(1, n + 1))))
