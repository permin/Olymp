#!/usr/bin/python

import math


def main():
    n = int(raw_input())
    for t in range(n):
        print "Case #%d:" % (t + 1),
        p, x, y = [int(z) for z in raw_input().split()]
        x -= 50
        y -= 50
        x *= 1.0 / 50
        y *= 1.0 / 50
        p *= 0.01
        if x * x + y * y > 1:
            print 'white'
        else:
            if x == 0 and y == 0:
                print 'white' if p == 0 else 'black'
            else:
                assert abs(x) > 0.001
                assert abs(y) > 0.001
                a = math.atan2(y, x)
                a = math.pi / 2 - a
                if a < 0.0:
                    a += 2 * math.pi
                assert 0 <= a < 2 * math.pi
                b = p * 2 * math.pi
                if b <= a:
                    print 'white'
                else:
                    print 'black'

main()
