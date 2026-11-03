
#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

/* Standard header files */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Return status macros */
#define SUCCESS 0
#define FAILURE 1
#define DATA_NOT_FOUND -1
#define LIST_EMPTY -2

/* Maximum size for word and filename arrays */
#define max 80

/* Singly linked list node to store input filenames */
typedef struct node
{
    char filename[max];       // Stores the filename
    struct node *link;        // Points to the next filename node
} Slist;


/* Sub-node structure to store file-wise word information */
typedef struct subnode
{
    int wordcount;             // Number of occurrences of the word in a file
    char filename[max];       // Name of the file containing the word
    struct subnode *sub_link; // Points to the next sub-node

} sub_node_t;


/* Main-node structure to store unique words */
typedef struct mainnode
{
    char word[max];                // Stores the unique word
    int file_count;                // Number of files containing this word
    struct mainnode *main_link;    // Points to the next main node
    struct subnode *sub_link;      // Points to the first sub-node

} main_node_t;


/* Hash table structure */
typedef struct hash
{
    int index;                 // Stores the hash index
    struct mainnode *link;     // Points to the first main node at this index

} hash_t;


/* Function declarations */

/* Read and validate command-line arguments */
int read_and_validate_arguments(char *str);

/* Insert a filename at the end of the singly linked list */
int insert_last(Slist **head, char *str);

/* Initialize the hash table */
int create_hash(hash_t *arr);

/* Create the inverted database using input files */
int create_database(Slist *head, hash_t *arr);

/* Display the complete inverted database */
void display_database(hash_t *arr);

/* Search for a word in the inverted database */
int search_database(hash_t *arr, char *str);

/* Save the inverted database into a file */
int save_database(char *str, hash_t *arr);

/* Update the database using a backup file */
int update_database(char *str, hash_t *arr);

/* Validate whether the input filename is valid */
int file_validation(char *str, Slist *head);

#endif
