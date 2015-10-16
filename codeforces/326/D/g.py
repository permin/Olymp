import random

n = 200*1000
q = 4000

print n,q
for i in range(n):
    print random.randint(0,10**9),

print
for i in range(q):
    t = random.choice([1,2])
    print t,
    l = random.randint(1,n)
    r = random.randint(l,n)
    print l, r,
    if t == 1:
        print random.randint(0,10**9),
    print


