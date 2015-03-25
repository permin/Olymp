#!/usr/bin/python

import random
import sys
from functions import *

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(Random(1,3), 20)())
#outS(SequenceGenerator(RandomString('ATGC', 200*1000), 2)())

if True:
    n = 3000
    print n
    for _ in range(n):
        out(SequenceGenerator(Random(-10000, 10000), 3)())


if False:
    n = 7
    m = 200*1000
    print n, m
    for _ in range(m):
        out(SequenceGenerator(Random(1, n), 2)())
