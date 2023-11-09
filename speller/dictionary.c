// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// crerate var
int num_of_word = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // crete var
    int hash_index = hash(word);

    // pointing to fist node
    node *cursor = table[hash_index];

    // iterate link list
    while (cursor != NULL)
    {
        // check the words same or not
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // move the cursor to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // crete var total
    unsigned int total_sum = 0;

    // var for len str
    int len = strlen(word);

    for (int n = 0; n < len; n++)
    {
        // Hashes word to a number
        total_sum += tolower(word[n]);
    }
    // create result
    long result = (total_sum % N);

    return result;

    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // create var char
    char word[LENGTH + 1];

    // open and read dict
    FILE *file = fopen(dictionary, "r");

    // return null if file cant open
    if (file == NULL)
    {
        return false;
    }
    // iterate one word at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));

        // copy word to node
        strcpy(n->word, word);

        // create var
        int hash_index = hash(word);

        // check if it is null
        if (n == NULL)
        {
            return false;
        }

        n->next = table[hash_index];
        table[hash_index] = n;

        // increment by 1
        num_of_word++;
    }
    fclose(file);
    // returning true if successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // condition must grater than 0
    if (num_of_word > 0)
    {
        return num_of_word; // return num of word
    }
    return 0; // or return 0
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int index = 0; index < N; index++)
    {
        // create var pointing for a node
        node *cursor = table[index];
        node *tmp = cursor;

        while (cursor != 0)
        {
            // var for temp
            tmp = cursor;

            // move cursor to next node
            cursor = cursor->next;

            // free temp
            free(tmp);
            tmp = cursor;
        }
        table[index] = 0; // make table null
    }
    return true; // returning true if successful
}
