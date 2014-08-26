buy = {}
sell = {}

import random

for i in range(10**5):
    s = random.choice(['sell', 'buy'])
    p = random.randint(1, 10**5)
    d = sell if s == 'sell' else buy
    x = d[p] if p in d else 0
    if x > 0:
        y = random.randint(-x, x + 1)
        d[p] += y
        print s, y, p
    else:
        y = random.randint(0, 10 + 1)
        if p not in d:
            d[p] = 0
        d[p] += y
        print s, y, p

print "end"

