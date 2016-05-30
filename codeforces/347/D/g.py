import random

n = 5000
h = 89
print n
for i in range(n):
    for _ in range(3):
        if h == 0 or i == 0:
            print random.choice([0, random.randint(0, 121)]),
        else:
            a = random.choice([0, random.randint(-121, 121)])
            if a < 0:
                h -= 1
            print a,
    print
