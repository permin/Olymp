def gen(g, p):
    a = set()
    x = 1
    for i in range(p - 1):
        a.add(x)
        x *= g
        x %= p
    return list(sorted(a))

def test(g, p):
    return len(gen(g,p)) == p - 1

def gcd(a, b):
    return gcd(b % a, a) if a > 0 else b

def phi(n):
    return len(filter(lambda x: gcd(x, n) == 1, range(1, n)))

def pr(n):
    return len(filter(lambda x: gcd(x, n) == 1 and test(x, n), range(1, n)))


for i in range(2, 1000):
    if phi(i) == i - 1:
        print i, pr(i), phi(i - 1)
        for j in range(2,i):
            if test(j, i):
                assert(len(gen(j, i*i*i)) == (i - 1) * i * i or
                    len(gen(j+i, i*i*i)) == (i - 1) * i * i
                        )




