/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"

int sizee = 100 , word_counter = 0;
char **dic;

/**
 * Compare two words case insensitively
 */

int valid (const char *word1 , char *word2)
{
    int min_length = strlen(word1)>strlen(word2) ? strlen(word2) : strlen(word1);
    for(int i = 0 ; i < min_length ; i++)
    {
        if(tolower(word1[i])<tolower(word2[i])) return -1;
        else if ((tolower(word1[i])>tolower(word2[i]))) return 1;
    }
    if(strlen(word1)==strlen(word2)) return 0;
    else if(strlen(word1)<strlen(word2)) return -1;
    else return 1;
}

/**
 * Returns true using binary search if word is in dictionary else false.
 */
bool check(const char *word)
{
    int start = 0 , end = word_counter-1;
    while(start <= end)
    {
        int mid = (start + end) / 2;
        if(valid(word,dic[mid])<0)
        {
            end = mid-1;
        }
        else if(valid(word,dic[mid])>0)
        {
            start = mid+1;
        }
        else
        {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *input_dic = fopen( dictionary , "r");
    if(input_dic ==NULL) return false;
    
    dic = (char **)malloc(sizee*sizeof(char *));
    dic[word_counter] = (char*)malloc(50*sizeof(char));

    while(fscanf(input_dic,"%s",dic[word_counter]) !=EOF)
    {
        word_counter++;
        if(word_counter==sizee)
        {
            sizee+=100;
            dic = (char**)realloc(dic,sizee*sizeof(char*));
        }
        dic[word_counter] = (char*)malloc(50*sizeof(char));
    }

    fclose(input_dic);
    return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0 ; i <= word_counter ; i++)
    {
        free (dic[i]);
    }
    free (dic);
    return true;
}
