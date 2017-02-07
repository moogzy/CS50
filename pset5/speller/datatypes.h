/**
 * Declares data structures for functionality.
 */

#ifndef DATATYPES_H
#define DATATYPES_H

/*
 * Hash table implementation
 * Use struct to store char array and next node
 */
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


#endif // DATATYPES_H
