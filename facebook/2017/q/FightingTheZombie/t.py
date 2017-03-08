#!/usr/bin/python


def parse_spell(spell):
    x, _, rem = spell.strip().partition('d')
    x = int(x)
    #print '{%s}' % rem
    if rem.isdigit():
        return (x, int(rem), 0)
    else:
        if '-' in rem:
            y, _, z = rem.partition('-')
            z = -int(z)
        elif '+' in rem:
            y, _, z = rem.partition('+')
            z = int(z)
        else:
            assert False
        y = int(y)
        return (x, y, z)


def solve(spell, zombie):
    times, sides, z = spell
    zombie
    distr = [1.0]
    for i in range(times):
        n_distr = [0.0] * (len(distr) + sides)
        for j in range(len(distr)):
            for p in range(1, sides + 1):
                n_distr[j + p] += 1.0 / sides * distr[j]
        distr = n_distr[:]

    m = zombie - z
    #print m
    m = max(m, 0)
    res = 0.0
    while m < len(distr):
        res += distr[m]
        m += 1
    #print distr, res
    assert abs(1.0 - sum(distr)) < 0.0001
    assert 0.0 <= res <= 1.0 + 1e-6
    return res


def main():
    tests = int(raw_input())
    for t in range(tests):
        zombie, spells_num = [int(x) for x in raw_input().split()]
        spells_line = raw_input().strip()
        spells = [parse_spell(x) for x in spells_line.split()]
        for (spell_str, spell) in zip(spells_line.split(), spells):
            x, y, z = spell
            if z == 0:
                s = "%dd%d" % (x, y)
            elif z > 0:
                s = "%dd%d+%d" % (x, y, z)
            else:
                s = "%dd%d%d" % (x, y, z)
            print s, spell_str
            assert s == spell_str
        res = 0.0
        for s in spells:
            res = max(res, solve(s, zombie))
        print "Case #%d: %0.6f" % (t + 1, res)


main()
