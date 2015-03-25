#!/usr/bin/python

s = raw_input()
p = s.split()
i = 0
while(i + 2 < len(p)):
    print p[i], p[i + 1], p[i + 2]
    i += 3

