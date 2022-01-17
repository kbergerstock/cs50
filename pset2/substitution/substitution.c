/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - vigenere's cipher

*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// encryption subroutine
const char *encode(const char *key, char *const str)
{
    int  k  = 0;
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(str[i]))     // if the char is a member of the alphabet
        {
            // calc the location of the encrypted value in the key
            k = tolower(str[i]) - 'a';
            // repace char in string with encrypted value
            // preserve case
            if (isupper(str[i]))
            {
                str[i] = toupper(key[k]);
            }
            else
            {
                str[i] = tolower(key[k]);
            }
        }
    }
    return str;
}

// validate the key contains alpha chars only
int validate_key(const char *k)
{
    int l = strlen(k);
    int *n = calloc(l + 1, sizeof(int));
    int i = 0;
    int r = 0;
    int c = 0;

    // check for correct size of key
    if (l < 26)
    {
        r = 1;
    }
    else
    {
        for (i = 0; i < l; i++)
        {
            // check for invalid chars in key
            if (!isalpha(k[i]))
            {
                r = 1;
                break;
            }
            else
            {
                // check for duplicate chars in key
                c = tolower(k[i]) - 'a';
                n[c] += 1;
                if (n[c] > 1)
                {
                    r = 1;
                    break;
                }
            }
        }
    }
    free(n);
    return r;
}

int main(int argc, char **argv)
{
    // allocate buffer to twice the size of a normal size tty terminal
    char *input_buffer = calloc(161, sizeof(char));
    int rtv = 1;

    if (argc == 2)
    {
        rtv = validate_key(argv[1]);
        if (rtv)
        {
            printf("Invalid key\n");
        }
        else
        {
            printf("plaintext:");
            char *c = fgets(input_buffer, 160, stdin);
            printf("ciphertext:%s\n", encode(argv[1], c));
        }
    }

    return rtv;
}