import random

n = 3000
m = 5000

print n, m
for _ in range(m):
    print (_ % n) + 1,
    print random.randint(1, n)
