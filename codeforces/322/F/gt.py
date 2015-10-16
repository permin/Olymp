import sys, random

n = int(sys.argv[1])

print n

m = (n) / 3
s = 1
f = m

for i in range(2, m + 1):
    print i - 1, i

g = s
i = m + 1

while i <= n:
    print i, g
    g = s + f - g
    i += 1
