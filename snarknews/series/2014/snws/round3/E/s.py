#!/usr/bin/python

import sys
import math

C= 4.0 / 3.0 * math.pi

t = int(input())

for _ in range(t):
    line = sys.stdin.readline()
    n, r = [int(x) for x in line.strip().split()]
    h = []
    v = []
    for i in range(n):
        line = sys.stdin.readline()
        a,b,c = [int(x) for x in line.strip().split()]
        h.append(0.5 * c)
        v.append(a * b * c)
    data = list(zip(h, v))
    data.sort()
    ok = True
    for i in range(n):
        if r > data[i][0]:
            oldV = C * (r**3)
            oldV += data[i][1]
            r = math.pow(oldV / C, 1.0 / 3.0)
        else:
            ok = False
    if not ok:
         print "Fail"
    else:
         print "Success"





