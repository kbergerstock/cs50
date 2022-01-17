/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - caesar's cipher
    I stopped depending on CS50 library and used standard 'c' libraries
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// encrypt the input string using the key
const char *encode_rot(int k, char *const s)
{
    char *t = s;    // obtain begining of message to encrypt
    char r;
    // bring the key into range of 0 through 25 using modulus division
    if (k < 0 || k > 26)
    {
        k = k % 26;
    }
    // process the string replacing each char with its cipher
    while (*t)
    {
        if (isalpha(*t))
        {
            // using 'a' as a constant keeps the key in range of 0-25
            r = 'a' + ((tolower(*t) - 'a' +  k)  % 26);
            // reverse the case stripping
            if (isupper(*t))
            {
                r = toupper(r);
            }
            // store the cipher
            *t = r;
        }
        t++;
    }
    return s;
}

int main(int argc, char **argv)
{
    // allocate buffer to twice the size of a normal size tty terminal
    char *input_buffer = calloc(161, sizeof(char));
    int rtv = 1;

    if (argc == 2)
    {
        printf("plaintext:");
        char *c = fgets(input_buffer, 160, stdin);
        // atoi converts everthing up to the first non digit
        // so at the worst case the key will be 0
        int k  = atoi(argv[1]);
        printf("ciphertext:%s\n", encode_rot(k, c));
        rtv = 0;
    }

    if (rtv == 1)
    {
        printf("Invalid key\n");
    }

    free(input_buffer);
    return rtv;
}
