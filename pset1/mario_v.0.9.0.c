/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - mario.c

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int get_int(void)
{
    int n = 0;
    int i = 0;
    const char buffer[81];
    char *b = (char *)buffer;
    char a = 0x00;
    *b = a;
    do
    {
        a = getchar();
        if (isdigit(a) || a == '-')
        {
            *b++ = a;
            *b = 0;
        }
    }
    while (strlen(buffer) < 80 && (isdigit(a) || a == '-'));
    n  = atoi(buffer);
    return n;
}

void dump_pyramid(int steps)
{
    int i;
    // initialize the output string
    char *s = malloc(4 + steps);
    // process the pyramid size in steps
    printf("\n");
    for (i = 0; i < steps; i++)
    {
        // add a step symbol
        strcat(s, "#");
        // print the output string forwards and backwards creating the pyramid shape
        printf("%*s  %-s\n", steps, s, s);
    }

    free(s);
}

int main(void)
{
    int steps = 0;
    // obtain pyramid size from user
    do
    {
        printf("number of steps: ");
        steps = get_int();
    }
    while (steps < 0 || steps > 23);

    // verify that the number of entered pyramid steps are valid and fit on the screen
    if (steps > 0 && steps <= 23)
    {
        // display the pyramid
        dump_pyramid(steps);
    }

    return 0;
}
