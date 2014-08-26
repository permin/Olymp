import sys
import random

n = int(sys.argv[1])
k = int(sys.argv[2])

print 1

a = [random.randint(1,10) for i in range(n)]

print len(set(a)), k

print >>sys.stderr, a

for i in range(k + 1):
    print sum(a),
    print >>sys.stderr, sum(a),
    for j in range(len(a)):
        if a[j] > 0:
            a[j] -= 1

print
print >>sys.stderr
