/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - greedy.c

*/


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// retuns as an integer the number of coins required to return the change
int get_coins(float amount)
{
    const float d[4] = { 0.25, 0.10, 0.05, 0.01 };
    int coins = 0;
    float t = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        t = floor(amount / d[i]);   // obtain the interger portion of denomination
        coins += (int)t;            // sum the denominations
        amount -= t * d[i];         // subtract denomination 8 qty from the amount
        amount += 0.00001;          // add in a correction factor
    }

    return coins;
}

int main(void)
{
    int coins = 0;
    float change = 0.0;
    const char buffer[81];
    do
    {
        printf("How much change is owed? ");
        fgets((char *)buffer, 80,  stdin);
        change = atof(buffer);
    }
    while (!isdigit(*buffer) || change < 0.0);

    if (change > 0.0)
    {
        coins = get_coins(change);
        printf("%d\n", coins);
    }

    return 0;
}