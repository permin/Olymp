#!/usr/bin/python

import sys

def main():
    with open(sys.argv[1], 'r') as f1:
        with open(sys.argv[2], 'r') as f2:
            lines1 = f1.readlines()
            lines2 = f2.readlines()

            for i in range(len(lines1)):
                r,a, b = lines1[i].strip().split()
                t,c, d = lines2[i].strip().split()
                assert a == c and r == t
                if b==d:
                    continue
                if abs(float(b) - float(d)) > 1e-7:
                    print r,a, "%s -> %s" % (b, d), "(%f)" % (abs(float(b)-float(d)))



main()
