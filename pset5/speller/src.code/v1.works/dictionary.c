/**
 * dictionary
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

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

const char *str2lower(const char *str)
{
    char *t = (char *)str;
    for (; *t; t++)
    {
        *t = tolower(*t);
    }
    return str;
}

const char *rtrim(const char *str)
{
    char *p = strchr(str, '\n');
    if (p != NULL)
    {
        *p = 0x00;
    }
    return str;
}

// duplicate word into storage and ensure it does not exceed LENGTH in size
static char *duplicate(const char *str)
{
    int k = strlen(str);
    char *p = NULL;
    if ((p = malloc(k + 1)) != NULL)
    {
        strcpy(p, str);
    }
    return p;
}

/* ----------  file locals --------------------------------*/

unsigned int num_words = 0;
bool initialized = false;
Word *wordList = NULL;

/* --------------------------------------------------------*/

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *szWord)
{
    // duplicating the iput word prevents it from being changed
    const char *szBuf = str2lower(duplicate(szWord));
    int mid, lower = 0;
    int upper = num_words;
    bool rtv = false;
    int results;
    while (lower <= upper && upper >= 0 && lower < num_words)
    {
        mid = (upper + lower) >> 1;
        results = strcmp(szBuf, wordList[mid]);
        if (results == 0)
        {
            rtv = true;
            upper = -1;
        }
        else if (results < 0)
        {
            upper = mid - 1;
        }
        else
        {
            lower = mid + 1;
        }
    }
    free((char *)szBuf);
    return rtv;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    int  storage = 150000;
    bool rtv = false;
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    char *sbuf = calloc(MAX_LENGTH, sizeof(char));
    char *szWord = NULL;
    // open the dictionary file
    FILE *fp = fopen(dictionary, "r");
    //set the input buffer size
    setvbuf(fp, buffer, _IOFBF, BUFFER_SIZE);
    num_words = 0;
    // allocate memory for the word list
    wordList = calloc(storage, sizeof(Word));
    // PROCESS the DICTIONARY FILE
    if (fp != NULL)
    {
        do
        {
            szWord = fgets(sbuf, WORD_LENGTH, fp);
            if (szWord != NULL)
            {
                wordList[num_words] = duplicate(rtrim(szWord));
                num_words++;
                // if the word list is insufficient in size
                if (num_words + 5 > storage)
                {
                    // duplicate the word list increasing the size
                    Word *tmp = wordList;
                    storage += 5000;
                    wordList = calloc(storage, sizeof(Word));
                    memcpy(wordList, tmp, (num_words * sizeof(Word)));
                    free(tmp);
                }
            }
        }
        while (szWord != NULL);
        //set the return value
        rtv = true;
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
    for (int i = 0; i < num_words; i++)
    {
        free(wordList[i]);
    }
    free(wordList);
    return true;
}
