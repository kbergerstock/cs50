#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char buffer[81];
    printf("enter your name >> ");
    fgets(buffer, 80, stdin);
    printf("hello, %s\n", buffer);
}
