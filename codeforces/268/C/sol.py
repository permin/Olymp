#!/usr/bin/env python

s = 45 * 18 * 10**17

a = int(raw_input())
s %= a
print (a - s), 10**18 + (a-s) - 1
