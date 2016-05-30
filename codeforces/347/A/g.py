import random

for i in range(100):
    if i > 0:
        print random.choice(["+", '-']),
    print "?",

print "=", random.randint(1, 1000 * 1000)
