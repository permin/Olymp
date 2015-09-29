#!/usr/bin/python

d=set()

def f(x, W):
    y = x % W
    if y == 0 or x % y != 0:
        return None
    A = (x-y)/W
    assert x / y == W * A / y + 1
    return x / y

def g(x, W):
    origin = x
    while True:
        z = f(x, W)
        if z == x or z is None:
            if z is not None:
                global d
                d.add(origin / z)
            return z
        x = z

W = 1024
for i in range(1, 500000):
    #print i, g(i, W)
    g(i,W)

print len(d)

