// lab2 scrabble.c
// krbergerstock2e4kountdown.com
// cs50

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define word_en 80

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(const char *word);

int main(void)
{
    char word1[word_len + 1];
    char word2[word_len + 1];
    // Get input words from both players
    fputs(stdout,"Player 1: ");
    fgets(word1,word_len,stdin);
    fputs(stdout,"Player 2: ");
    fgets(word2,word_len,stdin);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if(score1 == score2)
        fputs(stdout,"Tie Score\n");
    else if(score1 > score2)
        fputs(stdout,"Player 1 wins\n");
    else
        fputs(stdout,"player 2 wins\n");
}

int compute_score(const char *word)
{
    // TODO: Compute and return score for string
    int sum = 0;
    char *t = word;
    while(*t)
    {
        if isalpha(*t)
            sum += POINTS[tolower(*t++) - 'a'];
        else
            break;
    }
    return sum;
}