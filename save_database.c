
#include "inverted_search.h"

int save_database(char *str, hash_t *arr)
{
    /* Find the dot character in the filename */
    char *ch = strrchr(str, '.');

    /* Validate whether the filename has .txt extension */
    if(ch == NULL || strcmp(ch, ".txt") != 0)
    {
        fprintf(stderr, "file contain .txt\n");
        return FAILURE;
    }

    /* Open the backup file in write mode */
    FILE *fptr = fopen(str, "w");

    if(fptr == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        fclose(fptr);
        return FAILURE;
    }

    /* Traverse all 27 hash table indexes */
    for(int i = 0; i < 27; i++)
    {
        /* Check whether the current hash index contains main nodes */
        if(arr[i].link != NULL)
        {
            /* Access the first main node */
            main_node_t *main_temp = arr[i].link;

            /* Traverse all main nodes at the current hash index */
            while(main_temp != NULL)
            {
                /* Access the sub-node list of the current main node */
                sub_node_t *sub_temp = main_temp->sub_link;

                /* Write hash index, word and file count into the file */
                fprintf(fptr, "#%d;%s;%d;", i, main_temp->word, main_temp->file_count);

                /* Traverse all sub-nodes of the current main node */
                while(sub_temp != NULL)
                {
                    /* Write word count and filename into the backup file */
                    fprintf(fptr, "%d;%s;", sub_temp->wordcount, sub_temp->filename);

                    /* Move to the next sub-node */
                    sub_temp = sub_temp->sub_link;
                }

                /* Write ending delimiter and move to the next line */
                fputs("#\n", fptr);

                /* Move to the next main node */
                main_temp = main_temp->main_link;
            }
        }
    }

    /* Close the backup file */
    fclose(fptr);

    /* Return success after saving the database */
    return SUCCESS;
}
