#!/usr/bin/python

import random
import sys
from functions import *

v = 300
e = 1000;

print v, e
for i in range(e):
    out([Random(1,v)(), Random(1,v)(), Random(1, 100*1000)()])
print 1, v
