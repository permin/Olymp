#!/usr/bin/python

import random
import sys
from functions import *

#outS(SequenceGenerator(lambda x: x**x % 10, 20)())
#outS(SequenceGenerator(RandomString(AZ, 4), 20)())
n = 30000000
q = 20000000
print n, q
out(SequenceGenerator(Random(1,2000), n)())
out(SequenceGenerator(Random(1,n), q)())
