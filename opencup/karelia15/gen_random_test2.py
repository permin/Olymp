#!/usr/bin/python

import random
import sys
from functions import *

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(Random(1,3), 20)())
#outS(SequenceGenerator(RandomString(AZ, 4), 20)())
t = 1
print t
for i in range(t):
    n = 3000
    print n
    r = Random(-1000, 1000)
    for i in range(n):
        print r(), r(), r()
