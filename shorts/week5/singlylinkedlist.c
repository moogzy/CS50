#include <stdio.h>
#include <stdlib.h>

#define LENGTH 15

/*
 * Use struct to store int array and next node
 *
 * For singly linked list.
 */
typedef struct sllnode
{
    int number;
    struct sllnode *next;
}
sllnode;

// TODO - document
int main(void)
{
    
    int nums[] = {100, 750, 980, 2904, 2983, 8885};
    
    sllnode *head = malloc(sizeof(sllnode));
    head->number = 0;
    head->next = NULL;
    
   for(int i = 0; i < (sizeof(nums) / 4); i++)
   {
       sllnode *new_node = malloc(sizeof(sllnode));
       
       new_node->number = nums[i];
       new_node->next = head;
       head = new_node;
   }
   
   sllnode *trav = head;
   
   while(trav != NULL)
   {
       printf("Cycling through linked list from head to tail:\n");
       printf("%i\n", trav->number);
       sllnode *temp = trav;
       printf("Setting free the malloc for %i\n", trav->number);
       trav = trav->next;
       free(temp);
   }
}
