#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

typedef char *string;

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{

    char inbuf[81];
    // Check for invalid usage
    if (argc < 2)
    {
        fputs("Usage: runoff [candidate ...]\n", stdout);
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        fprintf(stdout, "Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }


    fputs("Number of voters: ", stdout);
    fgets(inbuf, 80, stdin);
    voter_count = atoi(inbuf);
    if (voter_count > MAX_VOTERS)
    {
        fprintf(stdout, "Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            fprintf(stdout, "Rank %i: ", j + 1);
            string name = fgets(inbuf, 80, stdin);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                fputs("Invalid vote.\n", stdout);
                return 4;
            }
        }

        fputs("\n", stdout);
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    fprintf(stdout, "%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    bool rtv = false;
    for (int ii = 0; ii < candidate_count; ii++)
    {
        int l = strlen(candidates[ii].name);
        int r = strncmp(candidates[ii].name, name, l);
        if (r ==  0)
        {
            preferences[voter][rank] = ii;
            rtv  = true;
            break;
        }
    }
    return rtv;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int k = preferences[i][j];
            if (!candidates[k].eliminated)
            {
                candidates[k].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int ndx = 0;
    int max_votes = 0;
    int needed = 1 + voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
            ndx = i;
        }
    }

    if (max_votes >= needed)
    {
        fputs(candidates[ndx].name, stdout);
        fputs("\n", stdout);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = INT_MAX;
    for (int ii = 0; ii < candidate_count; ii++)
    {
        if (!candidates[ii].eliminated)
        {
            if (candidates[ii].votes < min)
            {
                min = candidates[ii].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int ii = 0; ii < candidate_count; ii++)
    {
        if (candidates[ii].votes > min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int ii = 0; ii < candidate_count; ii++)
    {
        if (candidates[ii].votes == min)
        {
            candidates[ii].eliminated = true;
        }
    }
}
