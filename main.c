
/* Inverted_Search/
├── main.c
├── inverted_search.h
├── create_database.c
├── display_database.c
├── search_database.c
├── update_database.c
└── save_database.c
*/
/*INVERTED SEARCH

Name: SHAIK BAR SUHAIL 
Batch Number: 26012B
Roll Number: 26012B_119
Starting Date:25/10/2026
Ending Date:02/11/2026
input : ./a.out <file1.txt> <file2.txt> <file3.txt> <file4.txt> <file5.txt>
f1.txt successfully inserted file
f2.txt successfully inserted file
Succesfully created Hash Table

select your choice amoung the following options
1. Create Database
2. Display Database
3. Search database
4. save Database
5. update database
6. Exit

create Database:
Succussfully created database.

Display Database:
Index    Main Word            File Count   Word Count   Filename  
------------------------------------------------------------------------
8        I                    1            1            f2.txt               
                                           
         
18       suhail               1            1            f1.txt               
                                           
         
------------------------------------------------------------------------

search database:
Enter the string :suhail

------------------------------------------------------------------------
Word suhail is present in 1 files
In f1.txt ----> 1 times

------------------------------------------------------------------------

save Database:
Enter the file name to save the database :database.txt
succesfully saved at Database

update database:
Enter the backup file name :database.txt
succesfully updated database

*/
#include "inverted_search.h"

int main(int argc, char *argv[])
{
    // Initialize the filename linked list
    Slist *head = NULL;

    /* Here checking arguments */

    // Check whether the user passed command-line arguments
    if(argc == 1)
    {
        printf("pass Arguments \n");
        return SUCCESS;
    }

    /* Validations checking */

    // Traverse all command-line arguments
    for(int i = 1; i < argc ;i++)
    {
        // Check file extension, existence and whether the file is empty
        if(read_and_validate_arguments(argv[i]) == SUCCESS)
        {
            // Check whether the filename is already present in the linked list
            if(file_validation(argv[i], head) == FAILURE)
            {
                fprintf(stderr,"%s File Already Exists\n",argv[i]);
                continue;
            }

            // Insert the validated filename into the linked list
            if(insert_last(&head,argv[i]) == FAILURE)
            {
                fprintf(stderr,"%s Failed to insert file name\n",argv[i]);
            }
        }
    }

    // Declare an array containing 27 hash table entries
    hash_t arr[27];

    // Initialize the hash table
    if(create_hash(arr) == SUCCESS)
    {
        printf("Succesfully created Hash Table\n");
    }

    // Variable to store the menu option selected by the user
    int option = 0;

    // Execute the menu repeatedly until the user selects Exit
    do
    {
        printf("\nselect your choice amoung the following options\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search database\n");
        printf("4. save Database\n");
        printf("5. update database\n");
        printf("6. Exit\n");

        printf("Enter your option :");

        // Read the menu option from the user
        if(scanf("%d",&option) != 1)
        {
            // Clear invalid input from the input buffer
            while(getchar() != '\n');

            printf("please select correct option\n");
            continue;
        }

        // Perform the operation according to the selected option
        switch(option)
        {
            case 1:
            {
                // Create the inverted database using the input files
                if(create_database(head,arr) == FAILURE)
                {
                    fprintf(stderr,"failed create database\n");
                    break;
                }

                printf("Succussfully created database\n");
            }
            break;

            case 2:
            {
                // Display the complete inverted database
                display_database(arr);
            }
            break;

            case 3:
            {
                // Store the word entered by the user
                char str[50];

                printf("Enter the string :");
                scanf("%49s",str);

                // Search the given word in the hash table
                int res = search_database(arr,str);

                // Check whether the word is present in the database
                if( res == DATA_NOT_FOUND)
                {
                    fprintf(stderr,"%s it is not in Data base \n",str);
                }
                // Check whether the main linked list is empty
                else if(res == LIST_EMPTY)
                {
                    fprintf(stderr,"Main node NUll\n");
                }
            }
            break;

            case 4:
            {
                // Store the backup filename
                char str[25];

                printf("Enter the file name to save the database :");
                scanf("%24s",str);

                // Save the current database into the specified file
                if(save_database(str , arr) == FAILURE)
                {
                    fprintf(stderr,"failed to saves database\n");
                    break;
                }

                printf("succesfully saved at Database\n");
            }
            break;

            case 5:
            {
                // Store the backup filename entered by the user
                char str[25];

                printf("Enter the backup file name :");
                scanf("%24s",str);

                // Validate the backup file before updating the database
                if(read_and_validate_arguments(str) == SUCCESS)
                {
                    // Check whether the backup file is already present in the filename linked list
                    if(file_validation(str, head) == FAILURE)
                    {
                        fprintf(stderr,"%s File Already Exists\n",str);
                        break;
                    }
                    // Read backup data and reconstruct the hash table
                    if(update_database(str,arr) == FAILURE)
                    {
                        fprintf(stderr,"failed to update\n");
                        break;
                    }

                    printf("succesfully updated database\n");
                }
            }
            break;

            case 6:
            {
                // Free all nodes in the filename linked list
                while(head != NULL)
                {
                    Slist *temp = head;
                    head = head->link;
                    free(temp);
                }

                printf("Exiting the program\n");

                // Terminate the program
                exit(0);
                return SUCCESS;
            }
            break;

            // Handle invalid menu choices
            default :
                printf("Press correct option\n");
        }

    }while(option != 6);
}


// Function to validate the input filename
int read_and_validate_arguments(char *str)
{
    // Find the last occurrence of dot in the filename
    char *ch = strrchr(str,'.');

    // Check whether the file has a .txt extension
    if(ch == NULL || strcmp(ch,".txt") != 0)
    {
        fprintf(stderr,"%s File does'nt contain .txt \n",str);
        return FAILURE;
    }

    // Open the file in read mode
    FILE *fptr = fopen(str,"r");

    // Check whether the file exists
    if(fptr == NULL)
    {
        fprintf(stderr,"%s File Not exists\n",str);
        return FAILURE;
    }

    // Move the file pointer to the end of the file
    if(fseek(fptr,0,SEEK_END) != 0)
    {
        fclose(fptr);
        return FAILURE;
    }

    // Get the total size of the file
    long size = ftell(fptr);

    // Check whether the file is empty or ftell failed
    if(size <= 0)
    {
        printf("Please add some content in this file %s\n",str);
        fclose(fptr);
        return FAILURE;
    }

    // Close the file after validation
    fclose(fptr);

    return SUCCESS;
}


// Function to initialize the hash table
int create_hash(hash_t *arr)
{
    // Initialize all 27 hash table entries
    for(int i = 0 ;i < 27 ;i++)
    {
        // Assign the hash table index
        arr[i].index = i;

        // Initialize the main linked-list pointer
        arr[i].link = NULL;
    }

    return SUCCESS;
}


// Function to check whether a filename is already present
int file_validation(char *str, Slist *head)
{
    // Temporary pointer to traverse the filename linked list
    Slist *temp = head;

    // Traverse until the end of the linked list
    while(temp != NULL)
    {
        // Compare the current filename with the given filename
        if(strcmp(temp->filename,str) == 0)
        {
            fprintf(stderr,"%s File Already Exists\n",str);

            return FAILURE;
        }

        // Move to the next node
        temp = temp->link;
    }

    return SUCCESS;
}
