
#include "inverted_search.h"

void display_database(hash_t *arr)
{
    /* Print the database table headings */
    printf("\n%-8s %-20s %-12s %-12s %-10s\n",
       "Index",
       "Main Word",
       "File Count",
       "Word Count",
       "Filename");

    /* Print table separator */
    printf("------------------------------------------------------------------------\n");

    /* Traverse all 27 hash table indexes */
    for(int i = 0; i < 27; i++)
    {
        /* Check whether the current hash index contains any main node */
        if(arr[i].link != NULL)
        {
            /* Print the hash index */
            printf("%-8d ", i);

            /* Access the main node list */
            main_node_t *main_temp = arr[i].link;

            /* Traverse all main nodes at the current index */
            while(main_temp != NULL)
            {
                /* Print the word stored in the main node */
                printf("%-20s ", main_temp->word);

                /* Print the number of files containing this word */
                printf("%-12d ", main_temp->file_count);

                /* Access the sub-node list of the current main node */
                sub_node_t *sub_temp = main_temp->sub_link;

                /* Traverse all sub-nodes */
                while(sub_temp != NULL)
                {
                    /* Print the occurrence count of the word in this file */
                    printf("%-12d ", sub_temp->wordcount);

                    /* Print the filename */
                    printf("%-20s \n", sub_temp->filename);

                    /* Print empty columns for the next sub-node row */
                    printf("%-8s ", " ");
                    printf("%-20s ", " ");
                    printf("%-12s ", " ");

                    /* Move to the next sub-node */
                    sub_temp = sub_temp->sub_link;
                }

                /* Move to the next main node */
                printf("\n");
                main_temp = main_temp->main_link;

                /* Leave the index column empty for the next main node */
                printf("%-8s ", " ");
            }

            /* Add spacing between hash indexes */
            printf("\n");
        }
    }

    /* Print final table separator */
    printf("------------------------------------------------------------------------\n");
}
