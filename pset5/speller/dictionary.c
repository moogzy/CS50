/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "datatypes.h"

// 10000 makes the djb2 hash function effective(0.01 - 0.04 check time on avg).
// Large texts (eg shakespeare.txt will take a bit longer but still be considered fast.)
#define INDEXSIZE 10000

// Initialize array of node structs based on INDEXSIZE.
node *hashtable[INDEXSIZE];

// Initialize word counter.
int numWords = 0;

/**
 * Returns the hash key for a given word
 *
 * This is the djb2 hash function.
 * References: 
 * - http://www.cse.yorku.ca/~oz/hash.html
 * - http://www.partow.net/programming/hashfunctions/#StringHashing
 * 
 * Known to be one of the best hash functions for strings.
 */
unsigned long hash(const char *word)
{
    unsigned long hash = 5381;
    int cval = 0;

    while ((cval = *word++))
    {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + cval;
    }

    return hash % INDEXSIZE;
}


/*
 * Convert string to lower case
 */
char * strtolower(const char *word)
{
    // Determine the length of the word.
    int size = strlen(word);
    
    /* Allocate memory for a temporary char array
     *
     * This will store our temporary string as
     * word passed in is a const that is read only
     *
     *
     */
    char *tempword = malloc(size + 1);
    
    /* Write the end of string character to the
     * end of the tempword char array.
     *
     * This is necessary to ensure we enforce
     * the end of a string and don't go out ot bounds.
     */
    tempword[size] = '\0';
    
    /* Loop through word and convert each character
     * to lower string.
     * 
     * Write the converted character to the tempword array.
     *
     */
    for(int i = 0; word[i] != '\0'; i++)
    {
        tempword[i] = tolower(word[i]);
    }
    
    return tempword;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Enforce case-insensitive search, convert strings to lowercase.
    char *lowerword = strtolower((char *) word);

    if (lowerword == NULL)
    {
        unload();
        return false;
    }
    
    /* Create a traversal pointer so we 
     * have access to the head of the linked list
     * stored at this hashtable index.
     */
    node *trav = hashtable[hash(lowerword)];

    // Iterate through the linked list
    // looking for a match.
    while(trav != NULL)
    {
        /* Compare the dictionary word to the text word
         * If it matches it is spelled correctly.
         *
         * Then free the memory and return true.
         */
        if (strcmp(trav->word, lowerword) == 0)
        {
            free(lowerword);
            return true;
        }
        else
        {
            // Move to the next node struct
            // so we have access to the next word.
            trav = trav->next;
        }
    }
    // Didn't find the word in the dictionary.
    // Free the memory location and return false.
    free(lowerword);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // Reset memory allocated for hashtable array.
    // Overwrite the space with 0s.
    memset(&hashtable, 0, sizeof(hashtable));
    
    // Create a file pointer for the given dictionary file
    FILE *dictfp = fopen(dictionary, "r");
    
    /* If we couldn't open the file, report this.
     * unload the dictionary an return exit code 1.
     *
     * If we can open the file continue on with processing
     * the dictionary file.
    */
    if (dictfp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    else
    {
        // Establish a char array to store the word.
        char word[LENGTH + 1];
        
        // Until we hit the EOF, process each word
        // in at the given file pointer.
        while(fscanf(dictfp, "%s", word) != EOF)
        {
            /* On each new node dynamically allocate memory
             * based on the size of node struct.
             *
             *  node struct = 56B (46 for char array, 10 for next node pointer)
             *
             * This will be used to store the word.
             */
            node *new_node = malloc(sizeof(node));
            
            // Initialize new_node->next to be NULL
            new_node->next = NULL;
            
            /* If we can't allocate memory then we need to
             * unload the dictionary file and return false.
             *
             * If we can then access new_node struct to store
             * the word.
            */
            if (new_node == NULL)
            {
                unload();
                return false;
            }
            else
            {
                // Dereference new_node and access word
                // to copy the current dictionary word into the node.
                strcpy(new_node->word, word);
                
                // Determine hash key for given word.
                int hash_key = hash(new_node->word);
                
                /* Updating the linked list at the given hashtable index.
                 *
                 * To maintain the linked list(not lose existing links) we
                 * need to move the new_node.next value to point at the
                 * current head for the given array location aka
                 * hashtable[hash_key].
                 *
                 * Once pointing at the current head, we can safely make
                 * the new_node the head of the linked list.
                 *
                 */
                new_node->next = hashtable[hash_key];
                hashtable[hash_key] = new_node;
                
                // We've added the word to the dictionary
                // increment the word counter.
                numWords++;
            }
        }
        // We loaded the dictionary in memory successfully.
        // Close the dictionary file and return true.
        fclose(dictfp);
        return true;
    }
    // We haven't loaded the dictionary successfully.
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    /* Word counter is initialized to 0
     *
     * If we loaded the dictionary it is incremented
     * for each word added successfully.
     */
    return numWords;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // Cycle through the hash table to free
    // all dynamically allocated memory.
    for(int i = 0; i < INDEXSIZE; i++)
    {
        // Create a traversal node for the given hashtable
        // index.
        node *trav = hashtable[i];
        
        // As long as there are elements in the traversal node
        // keep going!
        while (trav != NULL)
        {
            // Assign the node to be set free to a temp var.
            node *temp = trav;
            
            // Move to the next node struct
            trav = trav->next;
            
            // Free our temp node struct friend
            free(temp);
        }
    }
    // Once we've cleared the data structures of all allocated memory
    // we can return true.
    return true;
}
