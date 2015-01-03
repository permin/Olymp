import functions
import sys

n = int(sys.argv[1])
m = int(sys.argv[2])
s = range(n*m)
ss = functions.shuffle(s[:])

print n, m
for i in range(n):
    for j in range(m):
        print s[i * m + j],
    print

for i in range(n):
    for j in range(m):
        print ss[i * m + j],
    print

