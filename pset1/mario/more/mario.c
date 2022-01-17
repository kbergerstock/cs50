/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - mario.c

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int get_steps(void)
{
    int steps = 0;
    const char buffer[81];
    do
    {
        // default the return value to force the while to repeat
        steps = -10;
        printf("number of steps: ");
        fgets((char *)buffer, 80, stdin);
        // verify that the buffer starts with a decimal digit (0..9)
        if (isdigit(*buffer))
        {
            // decode the buffer using atoi
            steps = atoi((char *)buffer);
        }
    }
    while (steps <= 0 || steps > 8);
    return steps;
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
        s[i] = '#';
        s[i + 1] = 0;
        // print the output string forwards and backwards creating the pyramid shape
        printf("%*s  %-s\n", steps, s, s);
    }

    free(s);
}

int main(void)
{
    // obtain pyramid size from user
    int steps = get_steps();

    // verify that the number of entered pyramid steps are valid and fit on the screen
    if (steps > 0 && steps <= 8)
    {
        // display the pyramid
        dump_pyramid(steps);
    }

    return 0;
}
