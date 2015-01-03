a = int(raw_input())

def s(n):
    r = 0
    while n > 0:
        r += n % 10
        n /= 10
    return r

def s1(n):
    if n < 10:
        return sum(range(0, n + 1))
    D = n % 10
    r = 0
    for d in range(10):
        if d <= D:
            r += d*(n / 10 + 1)
        else:
            r += d*(n / 10)
    r += s(n / 10) * (D + 1)
    r += s1((n / 10) - 1) * 10
    return r

def s2(n):
    r = 0
    for i in range(n + 1):
        r += s(i)
    return r


was = {}
was[0] = 0

x = 0
while True:
    assert x / a < 30
    x += a
    l = 0
    r = max(a, 100)
    while l + 1 < r:
        m = (l + r) / 2
        if s1(m) < x:
            l = m
        else:
            r = m
    k = s1(r) % a
    assert k < 2000
    if k in was:
        print was[k] + 1, r
        break

    was[k] = r



