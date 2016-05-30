import random
import sys

n = 1000
a = [random.randint(0, 100) for _ in range(n)]
b = [random.randint(0, 100) for _ in range(n)]

A = sum(a)
a = [1.0 * x / A for x in a]
A = sum(b)
b = [1.0 * x / A for x in b]

m = [0] * n
M = [0] * n

for i in range(n):
    for j in range(n):
        m[min(i, j)] += a[i] * b[j]
        M[max(i, j)] += a[i] * b[j]

print >>sys.stderr, sum(a)
print >>sys.stderr, sum(b)
print >>sys.stderr, sum(m)
print >>sys.stderr, sum(M)
print >>sys.stderr, a
print >>sys.stderr, b

for i in range(n):
    assert(abs(a[i] + b[i] - m[i] - M[i]) < 1e-6)

print n
for x in M:
    print x,
print
for x in m:
    print x,
print
