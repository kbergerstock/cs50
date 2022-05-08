# credit.py
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


def is_card_number_valid(ccn):
    d2f = [0, 2, 4, 6, 8, 1, 3, 5, 7, 9]   # look up table for value to sum for double digits
    k = len(ccn) - 1
    sum = 0
    c = 0

    while k >= 0:
        n = ord(ccn[k]) & 0x0f
        sum += n if c == 0 else d2f[n]
        c ^= 1
        k -= 1
    return True if sum % 10 == 0 else False


def what_card(ccn):
    L = len(ccn)
    if L == 15 and ccn[0] == '3' and (ccn[1] == '4' or ccn[1] == '7'):
        return 'AMEX'
    elif L == 16 and ccn[0] == '4':
        return 'VISA'
    elif (L == 13 or L == 16) and ccn[0] == '5' and (ccn[1] == '1' or ccn[1] == '2' or ccn[1] == '3' or ccn[1] == '4' or ccn[1] == '5'):
        return 'MASTERCARD'
    else:
        return 'INVALID'


def main():
    ccn = 'asd'
    while(not ccn.isdigit()):
        ccn = inputString("Enter Card Number:")

    if is_card_number_valid(ccn):
        print(what_card(ccn))
    else:
        print('INVALID')


if __name__ == "__main__":
    main()