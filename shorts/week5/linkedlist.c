/*
 * Hash table implementation
 * Linked list struct.
 * Use struct to store char array and next node
 */
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

        /* Dynamically allocate memory for a node to store the
         * head of the linked list.
         *
         * Intialize the next node as NULL for conditional purposes
         * as this identifies when we're adding the very first node to the
         * linked list.
        */
        node *head = malloc(sizeof(node));
        head->next = NULL;
        
    // Define a hashtable with 26 spots
    // a-z - 26 characters in the alphabet.
    node *hashtable[26];
    memset(&hashtable, 0, sizeof(hashtable));


                /* Adding very first node to the linked list.
                if (head->next == NULL)
                {
                    // Empty head becomes the current new_node.
                    head = new_node;
                    // Set next to a malloc'd node so we don't hit
                    // this condition on the next iteration.
                    head->next = malloc(sizeof(node));
                }
                // Subsequent nodes added to the linked list.
                else
                {
                   // To maintain the linked list we need to move
                   // the new_node.next value to point at the current head.
                   //
                   // This make new_node.next hold a pointer to the next node.
                   new_node->next = head;
                   
                   // Then we move the head node safely to point at the newly
                   // inserted node.
                   //
                   // This will make head the new head of the linked list.
                   head = new_node;
                }
                */
            }
            //TODO
        }
        node *trav = malloc(sizeof(node));
        for (int i = 0; i < LETTERSINALPHABET; i++)
        {
            trav = hashtable[i];
            printf("Linked List at location: hashtable[%i]\n", i);
            while (trav != NULL)
            {
                printf("%s\n", trav->word);
                trav = trav->next;
            }
        }