#!/usr/bin/python

n = 200 * 1000
print n
for _ in range(n / 2):
    print "+ 1"

i = 2
for _ in range(n / 4):
    print "+", i
    print '-'
    i += 1
