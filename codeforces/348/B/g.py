import random
n = 1000 * 1000
q = n * 2

print n, q
for _ in range(q):
    t = random.choice([1, 2])
    t = 2
    if t == 1:
        print t, random.randint(-n, n)
    else:
        print t
