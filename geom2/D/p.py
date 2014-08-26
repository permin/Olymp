import sys
import  math

p = []

for line in sys.stdin:
    p.append(tuple(float(x) for x in line.split()))

def dist(p1, p2):
    return sum([(x-y)**2 for (x,y) in zip(p1, p2)])

pd = []
for i in range(len(p)):
    for j in range(i + 1, len(p)):
        pd.append(dist(p[i], p[j]))

pd.sort()
print pd

rp = []

for i in range(len(p)):
    for j in range(i + 1, len(p)):
        for k in range(j + 1, len(p)):
            if abs(dist(p[i], p[j]) - pd[0]) < 1e-5 and \
                    abs(dist(p[k], p[j]) - pd[0]) < 1e-5 and \
                    abs(dist(p[i], p[k]) - pd[0]) < 1e-5:
                print  "cout << ", '"',
                c = []
                for d in range(3):
                    #print "%0.6f" % (sum([p[i][d], p[j][d], p[k][d]]) / 3.0 ),
                    c.append((sum([p[i][d], p[j][d], p[k][d]]) / 3.0 ))
                rp.append(tuple(c))
                l = math.sqrt(dist((0,0,0),c))
                for cc in c:
                    print "%0.6f" % (cc / l),

                print '\\n";'
print rp
print len(rp)

x = y= z = 0

pd2 = []

for r in rp:
    x += r[0]
    y += r[1]
    z += r[2]



print x, y, z

