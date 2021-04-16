# cash.py
#
# Keith R Bergerstock
# date: 2018.04.16


import sys


def inputString(prompt):
    """ returns a string from stdin """
    sys.stdout.write(prompt)
    sys.stdout.flush()
    tstr = sys.stdin.readline()
    return tstr.rstrip()


def inputInt(prompt):
    v = inputString(prompt)
    if v.isdigit():
        return int(v)
    else:
        return False


def inputFloat(prompt):
    v = inputString(prompt)
    for c in v:
        if not(c.isdecimal() or c == '.'):
            return False
    return float(v)


def getCoins(amount):
    """ returns the number of coins in the given amout """
    d = [0.25, 0.10, 0.05, 0.01]
    coins = 0.0
    for t in d:
        c = amount // t     # get the integer portion of the denomination
        coins += c          # sum the denominations
        amount -= c * t     # subtract from amount the current denimination value
        amount += 0.000001
    return int(coins)


def main():
    change = -1

    while(change < 0):
        r = inputFloat("How Much change is owed? ")
        if not r:
            change = -1
        elif r > 0:
            change = r
        else:
            change = 0

    if change > 0:
        print("{:d}".format(getCoins(change)))


if __name__ == "__main__":
    main()