#include <stdio.h>
#include <stdlib.h>

#define LENGTH 15

/*
 * Use struct to store int array and next node
 */
typedef struct node
{
    int number;
    struct node *next;
}
node;

// TODO - document
int main(void)
{
    
    int nums[] = {100, 750, 980, 2904, 2983, 8885};
    
    node *head = malloc(sizeof(node));
    head->number = 0;
    head->next = NULL;
    
   for(int i = 0; i < (sizeof(nums) / 4); i++)
   {
       node *new_node = malloc(sizeof(node));
       
       new_node->number = nums[i];
       new_node->next = head;
       head = new_node;
   }
   
   node *trav = head;
   
   while(trav != NULL)
   {
       printf("Cycling through linked list from head to tail:\n");
       printf("%i\n", trav->number);
       node *temp = trav;
       printf("Setting free the malloc for %i\n", trav->number);
       trav = trav->next;
       free(temp);
   }
}
