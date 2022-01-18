// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
    int generation;
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *p = calloc(1,sizeof(person));
    p->generation = GENERATIONS - generations;
  
    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // TODO: Randomly assign child alleles based on parents
        for(int i = 0; i < 2; i++)
        {
            int s = rand() % 2;
            p->alleles[i] = p->parents[i]->alleles[s];
        }
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        // TODO: Randomly assign alleles
        p->alleles[0] = random_allele();        
        p->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if(p != NULL )
    {
        // TODO: Free parents
        free_family(p->parents[0]);
        free_family(p->parents[1]);
 
        // TODO: Free child
        free(p);
    }
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation -- FIX remove loop
    char *ident = calloc(1 + generation * INDENT_LENGTH,sizeof(char));
    memset(ident, 0x20, generation * INDENT_LENGTH);
    // Print person
    printf("%sGeneration %i, blood type %c%c\n",ident, generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
    free(ident);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
