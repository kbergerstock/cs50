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
const char *encode_vigenere(const char *key, char *const str)
{
    char r;
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(str[i]))     // if the char is a member of the alphabet
        {
            // repace char in string with encrypted value
            // preserve case
            if (isupper(str[i]))
            {
                str[i] = toupper(key[i]);
            }
            else
            {
                str[i] = tolower(key[i]);
            }
         }
    }
    return str;
}

// validate the key contains alpha chars only
int validate_key(char *const k)
{
    int l = strlen(k);
    int i = 0;
    int r = 0;

    for (i = 0; i < l; i++)
    {
        r = isalpha(k[i]);
        if (r == 0)
        {
            break;
        }
    }
    return r == 0 ? 0 : 1;
}

int main(int argc, char **argv)
{
    // allocate buffer to twice the size of a normal size tty terminal
    char *input_buffer = calloc(161, sizeof(char));
    int rtv = 1;

    if (argc == 2)
    {
        if (validate_key(argv[1]))
        {
            printf("plaintext:");
            char *c = fgets(input_buffer, 160, stdin);
            printf("ciphertext:%s\n", encode_vigenere(argv[1], c));
            rtv = 0;
        }
    }
    if (rtv == 1)
    {
        printf("Invalid key\n");
    }
    return rtv;
}