/**
 * Implements a dictionary's functionality.
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


typedef struct node
{
    char *_word;
    struct node *next;
}node;

/**
 * Hash function to determine the index of the linked list
 * The index is determined through the following steps:
 * An initial value is given depending on the first letter of the word : 0 for A, 3 for B, 6 for C ... 75 for Z.
 * 0 is added if the word length is smaller than 5
 * 1 is added if the word length is greater than 4 but less than 9
 * 2 is added if the word length is greater than 8
 */

int hash_function(const char *word)
{
    return (tolower(word[0])-'a')*3+(strlen(word)>4)+(strlen(word)>8);
}

/**
 * Compare two word case independently
 */

bool compare (const char *word1, const char *word2)
{

    if(strlen(word1)!=strlen(word2)) return 0;
    int length = strlen(word1);
    for(int i = 0 ; i < length ; i++)
    {
        if(tolower(word1[i])!=tolower(word2[i])) return 0;
    }
   return 1;
}
node* dic[78] = {NULL}; //3*26

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int index = hash_function(word);
    node *ptr = dic[index];
    while(ptr!=NULL)
    {
        if(compare(ptr->_word,word)) return 1;
        else ptr = ptr->next;
    }
    return 0;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *open_dir = fopen(dictionary , "r");
    if(open_dir == NULL) return 0;

    char *word = malloc(50*sizeof(char));

    while( fscanf(open_dir , "%s" , word) != EOF)
    {
        int index = hash_function(word);
        if(dic[index]==NULL)
        {
            node *new = malloc(1*sizeof(node));
            new->_word = word;
            new->next = NULL;
            dic[index]= new;
        }
        else
        {
            node *add = malloc(1*sizeof(node));
            add->_word = word;
            add->next = dic[index];
            dic[index]= add;
        }

        word = malloc(50*sizeof(char));
    }
    free (word); //the last word which will be an EOF.
    fclose (open_dir);
    return 1;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int counter=0;
    for (int i = 0 ; i < 78 ; i++)
    {
        node *ptr = dic[i];
        if(ptr==NULL) continue;
        counter++;
        while(ptr->next!=NULL)
        {
            counter++;
            ptr = ptr->next;
        }
    }
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0 ; i < 78 ; i++)
    {
        node *ptr = dic[i];

        while(1)
        {
            if(ptr == NULL) break;
            node *temp = ptr;
            free(ptr->_word);
            ptr = ptr->next;
            free (temp);
        }

    }
    return 1;
}
