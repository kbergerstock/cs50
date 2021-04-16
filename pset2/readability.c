/*
    Keith R Bergerstock
    krbergerstock@e4kountdown.com
    CS50 - readability

*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUF_SIZE 512
float calc_colman_laiu(int sentences, int words, int letters)
{
    float L = (float)letters / (float)words * 100.0;
    float S = (float)sentences / (float)words * 100.0;
    return 0.0588 * L - 0.296 * S - 15.8;
}

int count_characters(const char *buffer)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;
    char u = 0;
    char *t = (char *)buffer;
    while (*t)
    {
        if (isalpha(*t))
        {
            letters++;
        }
        else if(*t == '!' || *t == '?1' || *t == '.')
        {
            sentences++;
            words++;
        }
        else if(*t == ',' || *t == '.')
        {
            words++;
        }
        else if(*t == ' ' && isalpha(u))
        {
            words++;
        }
        if (*t)
        {
            u = *t;
            t++;
        }
    }
    float cl = calc_colman_laiu(sentences, words, letters);
    int grade = (int)(cl + 0.5);
    return grade;
}


int main(void)
{
    char *buffer = calloc(MAX_BUF_SIZE,  sizeof(char));
    fputs("TEXT: ", stdout);
    fgets(buffer, MAX_BUF_SIZE, stdin);
    int grade = count_characters(buffer);
    if (grade < 1)
    {
        fputs("Before Grade 1\n", stdout);
    }
    else if (grade >= 16)
    {
        fputs("Grade 16+\n", stdout);
    }
    else
    {
        fprintf(stdout, "Grade %d\n", grade);
    }

    free(buffer);
    return 0;
}