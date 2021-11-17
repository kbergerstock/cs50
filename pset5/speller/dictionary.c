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
Word *wordList = NULL;

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
void add(Word* list,int n,const char* s)
{
    int k = strlen(s);
    list[n] = (char *)str2lower(rtrim(duplicate(s,k),k));
}

// returns the location of the word or -11 if not found
int binarySearch(Word szWord)
{
    int rtv = -11;
    switch (num_words)
    {   case 0:
            rtv = -11; break;
        case 1:
            rtv = 0;
            break;
        case 2:
        case 3:
            for(int i = 0; i < num_words; i++)
            {
                int results = strcmp(szWord, wordList[i]);
                if (results == 0)
                {
                    rtv = i;
                    break;
                }
            }
            break;
        default:
        {
            int mid, lower = 0;
            int upper = num_words;
            int results = 9991;
            do
            {
                mid = (upper + lower) >> 1;
                results = strcmp(szWord, wordList[mid]);
                if (results == 0)
                {
                    rtv = mid;
                }
                else if (results < 0)
                {
                    upper = mid - 1;
                }
                else if (results > 0)
                {
                    lower = mid + 1;
                }
            }  while (results != 0 && (mid != lower && mid != upper));
            break;
        }
    }
    return rtv;
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
    int ndx = hash(szBuf);
    if (ndx >= 0 && ndx < num_words)
    {
        int r = strcmp(szBuf,wordList[ndx]);
        if (r == 0)
        {
            rtv = true;
        }
    }
    free((char *)szBuf);
    return rtv;
}

unsigned int hash(const char *word)
{
    return binarySearch((Word) word);
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
    num_words = 0;
    // allocate memory for the word list
    wordList = calloc(storage, sizeof(Word));
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
    for (int i = 0; i < num_words; i++)
    {
        free(wordList[i]);
    }
    free(wordList);
    return true;
}
