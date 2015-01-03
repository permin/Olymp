def s(n):
    r = 0
    while n > 0:
        r += n % 10
        n /= 10
    return r

LEN = 521

sums = {}
sums[0] = 0

for i in range(1, 100000):
    sums[i] = sums[i - 1] + s(i)

dict = {}

for i in range(LEN, 100000):
    a = sums[i] - sums[i - LEN]
    if a not in dict:
        dict[a] = 0
    dict[a] += 1

m = min(dict)
M = max(dict)
print 1.0 * (M + m) /2 / LEN

parts = {}
parts[0] = 0
i = 1
for x in sorted(dict):
    parts[i] = parts[i - 1] + dict[x]
    i += 1

l = len(parts)
print parts[l/2] * 1.0 / parts[l - 1]
print (parts[int(0.55 * l)] - parts[int(0.45 * l)] ) * 1.0 / parts[l - 1]
