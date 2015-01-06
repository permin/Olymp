#!/usr/bin/python

"""words = {'int', 'double', '*', 'float'}

class Element(object):
    def __init__(s):
        self.data = []
        self.name = "UNDEFINED"


def convert(s):
    assert s[-1] == ';'
    if len(s) == 1:
        return ([], None)
    l = []
    pos = None
    if s[0] == ']':
        i = s.find(']')
        l_, pos_ = convert(s[i+1:])
        if pos_:
            pos = pos_
            l = [s[0:i+1]] + l_[:]
    elif s[0] == '(':
        b = 1
        i = 0:
        while b > 0:
            i += 1
            if s[i] == ')':
                b -= 1;
            elif s[i] == '(':
                b += 1
        l_, pos_ = convert(s[i+1:])
        if pos_:
            pos = pos_
        l = [Brackets(s[0:i])] + l_
    else:
        I = 0
        for i in range(len(s)):
            if s[:i] =
    return (l, pos)


'''class Brackets:
    def __init__(s):
        assert s[0] = ')' and s[-1] = ')'
        self '''

def main():
    try:
        s = raw_input().strip()
        print " ".join(s.split())
    except:
        print "Incorrect input"

main()"""

print '''8
void * (*d) (int ,    char *(*)(char *, char *), void * (*) (int ,    char *(*)(char *, char *)));
void * (*d) (int ,    char *(*)(char *, char *));
const int  * const p;
const int  * volatile const p;
float ( * ( *b()) [] )();
int *( *( *arr[5])())();
int (*p)(char);
int X::*foo
'''
