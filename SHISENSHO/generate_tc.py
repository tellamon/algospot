import sys
from random import randint
from random import choice


board = "ABCXY"
empty = [True, False]



def generate_tc() :

    W = randint(3,50)
    H = randint(3,50)
    print "{0} {1}".format(H, W)
    for h in range(H) :
        for w in range(W) :
            if(choice(empty)) :
                sys.stdout.write('.')
            else :
                sys.stdout.write(choice(board))
        sys.stdout.write('\n')

TC = 50
print TC
for t in range(TC) :
    generate_tc();