/**
 * dictionary
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "dictionary.h"

#define BUFFER_SIZE 8096
#define WORD_LENGTH (2 * LENGTH - 15)
#define MAX_LENGTH ( 2 * LENGTH)
/* ----------  file locals --------------------------------*/
typedef char *Word;

unsigned int num_words = 0;
bool initialized = false;

// Represents a node in a hash table
typedef struct node
{
    const char *word;
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int Buckets = 65535;
const unsigned int Limit = 65521;

// Hash table
node *hashTable = NULL;
/* --------------------------------------------------------*/


const char *str2lower(const char *str)
{
    if(str != NULL)
    {
        char *t = (char *)str;
        while(*t)
        {
            if (isalpha(*t))
            {
                *t = tolower(*t);
            }
            t++;
        }
    }
    return str;
}

const char *rtrim(const char *str, int k)
{
    if(str != NULL)
    {
        char *p = ((char *)str) + k;
        while(*p == 0x00 || *p == 0x20  || *p == 0x0d || *p ==  0x0a)
        {
            *p = 0x00;
            p--;
        }
    }
    return str;
}

// duplicate word into storage and ensure it does not exceed LENGTH in size
char *duplicate(const char *str, int k)
{
    char *p = malloc(k + 1);
    if ( p != NULL)
    {
        memcpy(p, str, k);
        *(p+k) = 0;
    }

    return p;
}

// add a new word to the list
void add(node *table, const char* s)
{
    int k = strlen(s);
    // duplicate the string remoinvg trailing white space and converting to lower case
    const char *szWord = str2lower(rtrim(duplicate(s,k),k));
    // get the hash value of the word
    int hdx = hash(szWord);
    // get a node pointer to table index of the hash value
    node *ptr = &table[hdx];
    // look for an empty node entry
    bool done = false;
    do{
        if(ptr->next == NULL && ptr->word == NULL)
        {
            // insert the word into the table
            ptr->word = szWord;
            // add an empty node to the next pointer
            ptr->next = calloc(1, sizeof(node));
            done = true;
        }
        else if(ptr->next == NULL)
        {
            ptr->next = calloc(1, sizeof(node));
            ptr = ptr->next;
        }
        else
        {
            ptr = ptr->next;
        }
    }while (!done);
}

/* --------------------------------------------------------*/

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *szWord)
{
    // duplicating the iput word prevents it from being changed
    int rtv = false;
    int k  = strlen(szWord);
    const char *szBuf = str2lower(rtrim(duplicate(szWord,k),k));
    int hdx = hash(szBuf);
    node *ptr  = &hashTable[hdx];
    bool done = false;
    int match = -11;
    do
    {
        if(ptr->word == NULL)
        {
            match = -11;
            done = true;
        }
        else
        {
            match = strcmp(szBuf,ptr->word);
        }
        if(match == 0)
        {
            rtv = true;
            done = true;
        }
        else
        {
            ptr = ptr->next;
        }

    }while(!done && ptr->next);
 
    free((char *)szBuf);
    return rtv;
}

unsigned int hash(const char *word)
{
    int hash = 0;
    int g = 31;
    char *s = (char *)word;
    while(isalpha(*s))
    {
        hash = (hash * g + (*s - 'a')) & 0xffffffff;
        s++;
    }
    return hash % Limit;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    bool rtv = false;
    char *buffer = calloc(1 + BUFFER_SIZE, sizeof(char));
    char *sbuf = calloc(1 + MAX_LENGTH, sizeof(char));
    char *szWord = NULL;
    num_words = 0;
    // allocate memory for the bucket list of hashes
    hashTable = calloc(Buckets, sizeof(node));
    // open the dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        rtv = false;
    }
    else
    {
        //set the input buffer size
        setvbuf(fp, buffer, _IOFBF, BUFFER_SIZE);
        do // PROCESS the DICTIONARY FILE
        {
            szWord = fgets(sbuf, WORD_LENGTH, fp);
            if (szWord != NULL)
            {
                add(hashTable, szWord);
                num_words++;
            }
        }
        while (szWord != NULL);
        //set the return value
        if(num_words > 0)
        {
            rtv = true;
        }
        // close the file
        fclose(fp);
    }
    // free tempary buffers
    free(sbuf);
    free(buffer);
    return rtv;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return num_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool unload(void)
{
    node *ptr = NULL;
    node * tmp = NULL;

    for (int i = 0 ; i < Limit; i++)
    {
        ptr = &hashTable[i];
        tmp = NULL;
        bool skip = true;
        while(ptr->word)
        {
            if(ptr->next)
            {
                free((char *)ptr->word);
                if(skip)
                {
                    skip = false;
                }
                else
                {
                    tmp = ptr;
                }
                ptr = ptr->next;
                if (tmp != NULL)
                {
                    free(tmp);
                }
            }
        }
    }
    free(hashTable) ;
    return true;
}
