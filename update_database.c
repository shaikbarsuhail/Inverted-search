
#include "inverted_search.h"

int update_database(char *str, hash_t *arr)
{
    /* Open the backup file in read mode */
    FILE *fptr = fopen(str, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "failed to open backup file\n");
        return FAILURE;
    }

    /* Variables to store data read from the backup file */
    char word[max];
    int filecount;
    int wordcount;
    char filename[max];

    int index;
    char ch;

    /* Read hash index, word and file count from the backup file */
    while(fscanf(fptr, "#%d;%79[^;];%d;",
                 &index, word, &filecount) == 3)
    {
        /* Allocate memory for a new main node */
        main_node_t *mainnode = malloc(sizeof(main_node_t));

        if(mainnode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return FAILURE;
        }

        /* Initialize the main node with the backup file data */
        strcpy(mainnode->word, word);
        mainnode->file_count = filecount;
        mainnode->main_link = NULL;
        mainnode->sub_link = NULL;

        /* Pointer to maintain the last sub-node */
        sub_node_t *sub_prev = NULL;

        /* Read all sub-nodes based on the file count */
        for(int i = 0; i < filecount; i++)
        {
            /* Read word count and filename */
            if(fscanf(fptr, "%d;%79[^;];",
                      &wordcount, filename) != 2)
            {
                fclose(fptr);
                fprintf(stderr, "file scanning failed\n");
                return FAILURE;
            }

            /* Allocate memory for a new sub-node */
            sub_node_t *subnode = malloc(sizeof(sub_node_t));

            if(subnode == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                return FAILURE;
            }

            /* Initialize the sub-node with backup file data */
            subnode->wordcount = wordcount;
            strcpy(subnode->filename, filename);
            subnode->sub_link = NULL;

            /* Insert the first sub-node */
            if(mainnode->sub_link == NULL)
            {
                mainnode->sub_link = subnode;
            }
            else
            {
                /* Attach the new sub-node at the end */
                sub_prev->sub_link = subnode;
            }

            /* Update the previous sub-node pointer */
            sub_prev = subnode;
        }

        /* Insert the main node into the corresponding hash index */
        if(index < 0 || index >= 27)
        {
            fprintf(stderr, "Invalid hash index %d\n", index);
            fclose(fptr);
            return FAILURE;
        }
        if(arr[index].link == NULL)
        {
            /* First main node at this hash index */
            arr[index].link = mainnode;
        }
        else
        {
            /* Traverse to the last main node */
            main_node_t *main_temp = arr[index].link;

            while(main_temp->main_link != NULL)
            {
                main_temp = main_temp->main_link;
            }

            /* Attach the new main node at the end */
            main_temp->main_link = mainnode;
        }

        /* Read the ending delimiter from the backup file */
        ch = fgetc(fptr);

        /* Check whether the current record has ended */
        if(ch == '#')
        {
            ch = fgetc(fptr);

            /* Check for newline before reading the next record */
            if(ch == '\n')
            {
                continue;
            }
        }
    }

    /* Close the backup file */
    fclose(fptr);

    /* Return success after updating the database */
    return SUCCESS;
}
