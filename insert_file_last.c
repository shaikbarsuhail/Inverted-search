
#include "inverted_search.h"

int insert_last(Slist **head, char *str)
{
    /* Allocate memory for a new node */
    Slist *new_node = malloc(sizeof(Slist));

    if(new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return FAILURE;
    }

    /* Copy the filename into the new node */
    strcpy(new_node->filename, str);

    /* Initialize the link of the new node to NULL */
    new_node->link = NULL;

    /* Check whether the linked list is empty */
    if(*head == NULL)
    {
        /* Make the new node the first node */
        *head = new_node;

        printf("%s successfully inserted file\n", new_node->filename);
        return SUCCESS;
    }

    /* Create a temporary pointer to traverse the linked list */
    Slist *temp = *head;

    /* Traverse until the last node is reached */
    while(temp->link != NULL)
    {
        temp = temp->link;
    }

    /* Connect the new node at the end of the linked list */
    temp->link = new_node;

    /* Print successful insertion message */
    printf("%s successfully inserted file\n", new_node->filename);

    return SUCCESS;
}
