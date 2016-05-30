import sys
sys.stdout = open("hack.txt", "w")
a = []
for i in xrange(12500):
    p = 8e-5 * (i + 1)
    q = 8e-5 * i
    a.append("%.8f" % (p * p - q * q))
print 12500
print " ".join(a)
print " ".join(reversed(a))
