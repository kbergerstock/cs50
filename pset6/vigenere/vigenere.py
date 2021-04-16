# python vigenere.py
#
# Keith R Bergerstock
# date: 2018.04.17

import sys


def inputString(prompt):
    """ returns a string from stdin """
    sys.stdout.write(prompt)
    sys.stdout.flush()
    tstr = sys.stdin.readline()
    return tstr.rstrip()


def get_case(c):
    return ord('a') if c >= 'a' and c <= 'z' else ord('A')


def normalize(c):
    return ord(c) - get_case(c)


def vigenere(c, k):
    """ encrypt a letter using the vigenere method """
    if c.isalpha():
        return chr(get_case(c) + ((normalize(c) + normalize(k)) % 26))
    else:
        return c


def encode(plaintext, key):
    j = 0
    cyphertext = ''
    for c in plaintext:
        cyphertext += vigenere(c, key[j])
        j += 1
        if j >= len(key):
            j = 0
    return cyphertext


def main():
    if len(sys.argv) == 2:
        if sys.argv[1].isalpha():
            plaintext = inputString("plaintext:")
            print("ciphertext:{}".format(encode(plaintext, sys.argv[1])))
        else:
            print("Invalid key")
            exit(1)
    else:
        print("Missing key")
        exit(1)


if __name__ == "__main__":
    main()