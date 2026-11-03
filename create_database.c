
#include "inverted_search.h"

int create_database(Slist *head, hash_t *arr)
{
    /* Pointer to traverse the file list */
    Slist *temp = head;

    /* Buffer to store each word read from the file */
    char str[50];

    /* Traverse all files present in the file list */
    while(temp != NULL)
    {
        /* Open the current file in read mode */
        FILE *fptr = fopen(temp->filename, "r");

        if(fptr == NULL)
        {
            printf("File opened failed\n");
            return FAILURE;
        }

        /* Read words from the current file one by one */
        while (fscanf(fptr, "%49s", str) == 1)
        {
            /* Extract the first character of the word */
            char ch = str[0];
            int index;

            /* Calculate hash index for uppercase letters */
            if(ch >= 'A' && ch <= 'Z')
            {
                index = ch - 'A';
            }
            /* Calculate hash index for lowercase letters */
            else if(ch >= 'a' && ch <= 'z')
            {
                index = ch - 'a';
            }
            /* Store special characters in index 26 */
            else
            {
                index = 26;
            }

            /* Access the main node list at the calculated hash index */
            main_node_t *main_temp = arr[index].link;
            main_node_t *main_prev = NULL;

            /* Traverse the main node list to search for the word */
            while(main_temp != NULL)
            {
                main_prev = main_temp;

                /* Check whether the word already exists */
                if(strcmp(main_temp->word, str) == 0)
                {
                    /* Access the sub-node list of the matching word */
                    sub_node_t *sub_temp = main_temp->sub_link;
                    sub_node_t *sub_prev = NULL;

                    /* Flag to identify whether filename already exists */
                    int flag = 0;

                    /* Traverse the sub-node list */
                    while(sub_temp != NULL)
                    {
                        sub_prev = sub_temp;

                        /* Check whether the current filename already exists */
                        if(strcmp(sub_temp->filename, temp->filename) == 0)
                        {
                            /* Increment word count for the existing filename */
                            sub_temp->wordcount++;
                            flag = 1;
                            break;
                        }

                        sub_temp = sub_temp->sub_link;
                    }

                    /* If filename is not present, create a new sub-node */
                    if(flag == 0)
                    {
                        sub_node_t *subnode = malloc(sizeof(sub_node_t));

                        if(subnode == NULL)
                        {
                            fprintf(stderr, "Memory allocation failed\n");
                            fclose(fptr);
                            return FAILURE;
                        }

                        /* Initialize word count */
                        subnode->wordcount = 1;

                        /* Check whether filename fits in the filename array */
                        if(strlen(temp->filename) >= sizeof(subnode->filename))
                        {
                            fprintf(stderr, "Filename too long\n");
                            free(subnode);
                            fclose(fptr);
                            return FAILURE;
                        }

                        /* Copy filename into the new sub-node */
                        strcpy(subnode->filename, temp->filename);

                        /* Initialize sub-node link */
                        subnode->sub_link = NULL;

                        /* Increment file count because a new filename is added */
                        main_temp->file_count++;

                        /* Attach the new sub-node at the end of the sub-node list */
                        sub_prev->sub_link = subnode;
                    }

                    /* Word is found, so stop searching the main node list */
                    break;
                }

                /* Move to the next main node */
                main_temp = main_temp->main_link;
            }

            /* If word does not exist, create a new main node */
            if(main_temp == NULL)
            {
                main_node_t *mainnode = malloc(sizeof(main_node_t));

                if(mainnode == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    fclose(fptr);
                    return FAILURE;
                }

                /* Initialize the new main node */
                strcpy(mainnode->word, str);
                mainnode->file_count = 1;
                mainnode->main_link = NULL;
                mainnode->sub_link = NULL;

                /* Allocate memory for the first sub-node */
                sub_node_t *subnode = malloc(sizeof(sub_node_t));

                if(subnode == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(mainnode);
                    fclose(fptr);
                    return FAILURE;
                }

                /* Initialize the first sub-node's word count */
                subnode->wordcount = 1;

                /* Check filename length before copying */
                if(strlen(temp->filename) >= sizeof(subnode->filename))
                {
                    fprintf(stderr, "Filename too long\n");
                    free(subnode);
                    fclose(fptr);
                    return FAILURE;
                }

                /* Store filename in the sub-node */
                strcpy(subnode->filename, temp->filename);

                /* Initialize sub-node link */
                subnode->sub_link = NULL;

                /* Connect the first sub-node to the main node */
                mainnode->sub_link = subnode;

                /* Insert the new main node into the hash table */
                if(arr[index].link == NULL)
                {
                    /* First node in this hash index */
                    arr[index].link = mainnode;
                }
                else
                {
                    /* Insert the main node at the end of the list */
                    main_prev->main_link = mainnode;
                }
            }
        }

        /* Close the current file after reading all its words */
        fclose(fptr);

        /* Move to the next file in the file list */
        temp = temp->link;
    }

    /* Return success after processing all files */
    return SUCCESS;
}
