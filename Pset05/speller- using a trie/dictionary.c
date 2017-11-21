/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

/**
 * Declare the structure used in each element of the trie_node's array
 *
 * The two structs are circular dependant so they both need to be declared in the header file or we just can declare the trie_node struct up here
 * They are only declared and not defined since they'll both be called using pointers
 * more about this in this link : https://stackoverflow.com/questions/2732978/c-how-to-declare-a-struct-in-a-header-file
 */

struct trie_node;

typedef struct element
{
    bool x; // Word marker
    struct trie_node *_ptr; // Pointer to another Trie node
} element;


/**
 * Declare the Trie data structure
 */
typedef struct trie_node{
    struct element *arr[27];
}trie_node;

/**
 * Declare a global trie_node pointer to point at the root node of the trie and an int counter to count the words in the dic
 */
trie_node *root; int counter;



/** Recursivly unload the trie
 */

bool rec_unload(trie_node *ptr)
{
    // Iterate through all the elements of a specific node's array
    for(int i = 0 ; i < 27 ; i++)
    {
        // Recurse all the way until we find a node having all its array pointers pointing to null
        if(ptr->arr[i]->_ptr!=NULL) rec_unload(ptr->arr[i]->_ptr);

        // Free the elements of this array
        free(ptr->arr[i]);
    }
    // Free the pointer to this array
    free(ptr);
    return true;
}

/**
 * Initialize all the values in the array of the given trie_node to NULL
 */
void init(trie_node *ptr)
{
    for(int i=0 ; i < 27 ; i++)
    {
        // Alocate the space needed for element in the trie_node
        ptr->arr[i] = malloc(sizeof(element));
        // Set all the pointers to other nodes to null
        ptr->arr[i]->_ptr=NULL;
        // Set all the word markers to 0
        ptr->arr[i]->x = 0;
    }

}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    trie_node *ptr = root;

    // The apostrophe is indicated at index 26, so we will replace it in temp by a '}' which the character that follows 'z' ie. '}'-'a' = 26.
    char temp[50];
    strcpy(temp,word);

    for(int i = 0 , size = strlen(word) ; i <size ; i++)
    {
        //replace the apotrophe with a '{'.
        if(temp[i]==39) temp[i]='{';

        if(ptr->arr[ tolower(temp[i])-'a']->_ptr == NULL && ptr->arr[ tolower(temp[i])-'a']->x==0) return false;

        if(i==size-1 && ptr->arr[ tolower(temp[i])-'a']->x==0) return false;

        ptr = ptr->arr[ tolower(temp[i])-'a']->_ptr;

        if(ptr == NULL && i != size-1) return false;
    }
    return true;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *open_dir = fopen(dictionary , "r");
    if(open_dir == NULL) return false;

    root = malloc(sizeof(trie_node));
    init (root);

    char word[50];

    while( fscanf(open_dir , "%s" , word)!=EOF )
    {
        counter++;
        trie_node *ptr = root;
        for(int i = 0 , size = strlen(word) ; i < size ; i++)
        {
            // All apostrophes will be stored in the dictionary as '{'.
            if(word[i]==39) word[i]='{';

            // If this is the first word to be encountered that starts with a specific letter
            if( ptr->arr[ word[i]-'a']->_ptr == NULL && i!= size-1)
            {
               ptr->arr[ word[i]-'a']->_ptr = malloc (sizeof(trie_node));
               ptr = ptr->arr[ word[i]-'a']->_ptr;
               init (ptr);
            }

            // If this is the last letter
            else if (i == size-1)
                ptr->arr[ word[i]-'a']->x=1;

            // Else if this letter appeared before
            else
                ptr = ptr->arr[ word[i]-'a']->_ptr;
        }
    }
    fclose (open_dir);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    return rec_unload(root);
}
