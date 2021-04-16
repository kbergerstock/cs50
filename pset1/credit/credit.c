/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - credit.c

*/



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50
#define TRUE 1
#define FALSE 0

#define AMEX 0
#define VISA 1
#define MASTERCARD 2
#define INVALID 3

// look up table for card types
const char *types[4] = { "AMEX", "VISA", "MASTERCARD", "INVALID" };
// look up table for number to sum for doubled digits
const int d2f[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };

// module to verify a card number
int is_card_number_valid(int *ccn, int len)
{
    int k;
    int c = 0;
    int sum = 0;

    for (k = len - 1; k >= 0 ; k--)
    {
        sum += (c == 0 ? ccn[k] : d2f[ccn[k]]);
        c ^= 1;
    }

    return sum % 10 == 0 ? TRUE : FALSE;
}
// module to determine what type of card it is
int what_card(int *ccn, int len)
{
    int r = INVALID;
    if (len == 15 && ccn[0] == 3 && (ccn[1] == 4 || ccn[1] == 7))
    {
        r = AMEX;
    }
    else if (len == 16 && ccn[0] == 4)
    {
        r = VISA;
    }
    else if ((len == 13 || len == 16) && ccn[0] == 5 && (ccn[1] >= 1 && ccn[1] <= 5))
    {
        r = MASTERCARD;
    }
    return r;
}


int main(void)
{
    // allocate buffers
    const char buffer[MAX_LEN + 1];
    int  ccn[MAX_LEN + 1];

    // set default output to invalid
    int L = 0;
    int r = FALSE;
    int n = 0;
    
    // obtain user input
    do
    {
        printf("Enter Card Number:");
        fgets((char *)buffer, MAX_LEN ,stdin);
        // subtract 1 from len to account for line feed at end of buffer
        n = strlen(buffer) - 1; 
        // convert input buffer to integer array
        for (r = FALSE, L = 0; L < n; L++)
        {
            if(isdigit(buffer[L]))
            {
                ccn[L] = buffer[L] & 0x0F;
            }
            else
            {
                r = TRUE;
                break;
            }
        }
    }
    while (r);


    // determine card type
    if (is_card_number_valid(ccn, L))
    {
        r = what_card(ccn, L);
    }
    else
    {
        r = INVALID;
    }

    // output card type
    printf("%s\n", types[r]);
    return 0;
}