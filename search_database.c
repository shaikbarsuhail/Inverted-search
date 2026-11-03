
#include "inverted_search.h"

int search_database(hash_t *arr, char *str)
{
    /* Variable to store the calculated hash index */
    int index;

    /* Calculate hash index for uppercase letters */
    if(str[0] >= 'A' && str[0] <= 'Z')
    {
        index = str[0] - 'A';
    }
    /* Calculate hash index for lowercase letters */
    else if(str[0] >= 'a' && str[0] <= 'z')
    {
        index = str[0] - 'a';
    }
    /* Store special characters at index 26 */
    else
    {
        index = 26;
    }

    /* Access the main node list at the calculated hash index */
    main_node_t *main_temp = arr[index].link;

    /* Check whether the hash index is empty */
    if(main_temp == NULL)
    {
        return LIST_EMPTY;
    }

    /* Traverse the main node list to search for the given word */
    while(main_temp != NULL)
    {
        /* Compare the current main node word with the search word */
        if(strcmp(main_temp->word, str) == 0)
        {
            /* Display word search result */
            printf("\n------------------------------------------------------------------------\n");

            /* Print the word and number of files containing it */
            printf("Word %s is present in %d files\n",
                   main_temp->word, main_temp->file_count);

            /* Access the sub-node list of the matching word */
            sub_node_t *sub_temp = main_temp->sub_link;

            /* Traverse all sub-nodes to display file-wise word count */
            while(sub_temp != NULL)
            {
                /* Print filename and number of occurrences in that file */
                printf("In %s ----> %d times\n",
                       sub_temp->filename, sub_temp->wordcount);

                /* Move to the next sub-node */
                sub_temp = sub_temp->sub_link;
            }

            /* Print closing separator */
            printf("\n------------------------------------------------------------------------\n");

            /* Return success because the word was found */
            return SUCCESS;
        }

        /* Move to the next main node */
        main_temp = main_temp->main_link;
    }

    /* Return DATA_NOT_FOUND if the word does not exist in the hash index */
    return DATA_NOT_FOUND;
}
