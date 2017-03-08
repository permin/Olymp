import random
import string

class Const(object):
    def __init__(self, n):
        self.n = n
    def __call__(self, *args):
        return self.n

class Random(object):
    def __init__(self, min, max):
        self.min = min
        self.max = max

    def __call__(self, *args):
        return random.randint(self.min, self.max)

AZ = string.ascii_uppercase;
Az = string.ascii_letters
az = string.ascii_lowercase
digits = string.digits

class RandomString(object):
    def __init__(self, alpha, len):
        self.len = len
        self.alpha = alpha

    def __call__(self, *args):
        return "".join([random.choice(self.alpha) for _ in range(self.len)])

class SequenceGenerator(object):
    def __init__(self, generator, len):
        self.g = generator
        self.len = len
    def __call__(self, *args):
        return [self.g(x) for x in range(self.len)]

def shuffle(a):
    random.shuffle(a)
    return a

def out(a):
    print " ".join([str(x) for x in a])

def outS(a):
    print len(a)
    out(a)
