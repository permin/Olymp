import sys

for line in sys.stdin:
    a,b=line.strip().split()
    print "letterPrice[%s]=%s;" % (a,b)
