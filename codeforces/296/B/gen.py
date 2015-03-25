import random
import sys

n = int(sys.argv[1])
print n

was = set([None])

for i in range(0, n):
    x = None
    while x in was:
        x = random.randint(0, 10000000)

    print x,
    was.add(x)
    print random.randint(0, 1000)
