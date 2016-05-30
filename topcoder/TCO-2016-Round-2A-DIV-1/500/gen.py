import random


def pt(n, a, b, c):
    print -1

    def p(a):
        print "{%s}" % (','.join([str(x) for x in a]))
    print n
    p(a)
    p(b)
    p(c)


def test1():
    n = 45
    a = []
    b = []
    c = []

    for i in range(n):
        for j in range(i + 2, n):
            a.append(i)
            b.append(j)
            c.append(1)
    pt(n, a, b, c)


def test2():
    n = 45
    a = []
    b = []
    c = []

    for i in range(n):
        for j in range(i + 1, n):
            a.append(i)
            b.append(j)
            c.append(1)
    pt(n, a, b, c)

test1()
