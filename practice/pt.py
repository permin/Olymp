
import random

def steps(b, a):
    x = 0
    t = 0
    while b < x < a:
        x += random.choice([-1,+1])
        t += 1
    return (t, x)

def solve(b, a):
    num = 100000
    avg = 0
    A = 0
    for i in range(num):
        (E, x) = steps(b, a)
        avg += 1.0 / num * E
        A += 1 if x == a else 0
    print -b * a, avg, 1.0 * A / num, - 1.0 * b / (a - b)

for i in range(1, 20):
    for j in range(-20, 0):
        solve(j, i);
