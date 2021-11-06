#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 40

int main(void)
{
    char input_buffer[BUFSIZE];
    int start_pop_size = 0;
    int end_pop_size = 0;
    int years = 0;

    // TODO: Prompt for start size
    do
    {
        input_buffer[0] = 0;
        fputs("enter starting population size: ",stdout);
        fgets(input_buffer,BUFSIZE,stdin);
        start_pop_size = atoi(input_buffer);
    } while(start_pop_size < 9);

    // TODO: Prompt for end size
    do{
        input_buffer[0] = 0;
        fputs("enter ending population size: ",stdout);
        fgets(input_buffer,BUFSIZE,stdin);
        end_pop_size = atoi(input_buffer);
    } while(end_pop_size <= start_pop_size);

    // TODO: Calculate number of years until we reach threshold
    while(start_pop_size < end_pop_size)
    {
        int growth = start_pop_size / 3;
        int loss   = start_pop_size / 4;
        start_pop_size += (growth - loss);
        printf(" %d %d %d \n",growth,loss,start_pop_size);
        years++;
    } 

    // TODO: Print number of years
    fprintf(stdout,"years: %d\n",years);
}