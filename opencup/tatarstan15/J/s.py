def pro(a, b):
    r = 1
    for i in range(a, b + 1):
        r *= i
    return r

def f(n):
    return pro(1, n)

def C(n, k):
    return f(n) / f(k) / f(n-k)

def r():
    mod = list(range(2, 50))
    n = 2130
    k = 109
    for m in mod:
        print m, (C(n,k) % m)

#print pro(1, 2116 - 1) % 47
#print (f(2130)/ (47**19)) % 47

def r2():
    mod = list(range(2, 50))
    n = 20
    k = 9
    for m in mod:
        print m, (C(n,k) % m)


def maxP(n, p):
    i = 0
    while n % p == 0:
        n /= p
        i += 1
    return i

print maxP(f(20), 3)
print maxP(f(9), 3)
print maxP(f(11), 3)
print (f(18) / (3**8)) % 3

#print pro(1, 2116 - 1) % 47
#print (f(2130)/ (47**19)) % 47
