#!/usr/bin/python

import sys


def main():
    urls = []
    for line in sys.stdin:
        if 'http' in line:
            urls.append(line[7:].strip())

    paths = {}
    for url in urls:
        if '/' in url:
            a, _, b = url.partition('/')
            b = '/' + b
        else:
            a, b = url, ''
        if a not in paths:
            paths[a] = set()
        paths[a].add(b)
    ans = {}
    for key in paths:
        h = hash(tuple(x for x in paths[key]))
        if h not in ans:
            ans[h] = []
        ans[h].append(key)

    k = 0
    for url in ans:
        if len(ans[url]) > 1:
            k += 1
    print k
    for url in ans:
        if len(ans[url]) > 1:
            print ' '.join("http://%s" % s for s in ans[url])

main()
