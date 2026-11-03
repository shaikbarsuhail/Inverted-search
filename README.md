# Inverted Search Project

## Project Description

Inverted Search is a C project that creates a database of words from multiple text files using a Hash Table and Linked Lists. It allows users to search for a word and identify the files in which it appears.

## Technologies Used

- C Programming
- Data Structures
- Hash Table
- Singly Linked Lists
- File Handling
- Dynamic Memory Allocation

## Project Files

- `main.c` – Main function and menu-driven execution.
- `inverted_search.h` – Structure definitions and function declarations.
- `create_database.c` – Creates the inverted database.
- `display_database.c` – Displays the database.
- `search_database.c` – Searches for a word in the database.
- `save_database.c` – Saves the database into a backup file.
- `update_database.c` – Updates the database from a backup file.

## Features

- Read and validate input files.
- Create a database of unique words.
- Maintain word counts for each file.
- Display the complete database.
- Search for a particular word.
- Save the database into a backup file.
- Update the database using a backup file.

## Input Files

Before running the program, create two text files named `f1.txt` and `f2.txt` in the project folder.

Add the following sample contents:

**f1.txt**
```text
hello world hello
welcome to embedded systems
```

**f2.txt**
```text
hello welcome
world programming in C
```

Make sure both files contain some text and are saved in the project directory.

## How to Run in VS Code

### Prerequisites

- Visual Studio Code
- GCC compiler
- C/C++ extension for VS Code

### Step 1: Clone the Repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### Step 2: Open the Project

Open the cloned project folder in Visual Studio Code.

### Step 3: Compile the Program

Open the VS Code terminal and execute:

```bash
gcc *.c
```

### Step 4: Run the Program

Pass the input text filenames as command-line arguments:

```bash
./a.out f1.txt f2.txt
```

### Step 5: Select an Operation

After execution, the program displays the following menu:

1. Create Database
2. Display Database
3. Search Database
4. Save Database
5. Update Database
6. Exit

Select the required option to perform the operation.

## Concepts Learned

- Hash Table implementation
- Singly Linked List operations
- File handling in C
- Dynamic memory allocation
- Database creation and searching

## Author

**Shaik Bar Suhail**

C Programming and Data Structures Trainee at Emertxe.

LinkedIn: www.linkedin.com/in/suhail-s-b-3571822b6

