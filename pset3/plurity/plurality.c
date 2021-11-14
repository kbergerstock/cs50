#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9
#define BUFSIZE 128

typedef char *string;

// Candidates have name and vote count
typedef struct
{
    char *name;
    int votes;
}

candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, string argv[])
{
    char inbuf[BUFSIZE];
    // Check for invalid usage
    if (argc < 2)
    {
        fputs("Usage: plurality [candidate ...]\n", stdout);
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        fprintf(stdout, "Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1 ];
        candidates[i].votes = 0;
    }

    fputs("number of voters: ",stdout);
    fgets(inbuf, BUFSIZE, stdin);
    int voter_count = atoi(inbuf);
    if(voter_count == 0)
    {
        fputs("No votes to count",stdout);
        return 0;
    }

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        fputs("Vote: ", stdout);
        fgets(inbuf, BUFSIZE, stdin);

        // Check for invalid vote
        if (!vote(inbuf))
        {
            fputs("Invalid vote.\n", stdout);
        }
    }

    // Display winner of election
    print_winner();
    return 0;
}

// Update vote totals given a new vote
bool vote(char* name)
{
    bool rtv = false;
    for (int ii = 0; ii < candidate_count; ii++)
    {
        int l = strlen(candidates[ii].name);
        int r = strncmp(candidates[ii].name, name, l);
        if ( r ==  0)
        { 
            candidates[ii].votes++;
            rtv  = true;
            break;
        }
    }
    return rtv;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == max_votes)
        {
            fputs(candidates[j].name, stdout);
            fputs("\n",stdout);
        }
    }
}

