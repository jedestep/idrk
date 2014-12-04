import sys
import random
alpha = ['A','C','G','T']

with open(sys.argv[1], 'w') as f:
    for i in xrange(1,10001):
        f.write(random.choice(alpha))
        if i and i % 100 == 0:
            f.write('\n')
