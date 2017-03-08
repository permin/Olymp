#!/usr/bin/python


def main():
    t = int(raw_input())
    for i in range(t):
        print "Case #%d:" % (i + 1),
        n = int(raw_input())
        a = [None] * n
        for k in range(n):
            a[k] = int(raw_input())
        a.sort()
        res = 0
        while a and a[-1] * len(a) >= 50:
            take = 1
            while take * a[-1] < 50:
                take += 1
            a = a[take - 1: -1]
            res += 1

        print res


main()
