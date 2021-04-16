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

const char *str2lower(const char *str, int len)
{
    if(str != NULL)
    {
        char *t = (char *)str;
        for(int k = 0; k < len; k++)
        {
            t[k] = tolower(t[k]);
        }
    }
    return str;
}

const char *rtrim(const char *str, int k)
{
    if(str != NULL)
    {
        char *p = ((char *)str) + k;
        while( *p == 0x00 || *p == 0x20  || *p == 0x0d || *p ==  0x0a)
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
    char *p = NULL;
    if ((p = malloc(k + 1)) != NULL)
    {
        memcpy(p, str, k);
    }
    return p;
}

// add a new word to the list
void add(Word* list,int n,const char* s)
{
    int k = strlen(s);
    list[n] = (char *)str2lower(rtrim(duplicate(s,k),k),k);
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
    int k  = strlen(szWord);
    const char *szBuf = str2lower(rtrim(duplicate(szWord,k),k),k);
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
                add(wordList,num_words,szWord);
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
