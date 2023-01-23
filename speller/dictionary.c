// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <math.h>
#include <string.h>

typedef uint8_t BYTE;

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
int dict_size = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word to obtain hash value
    int hash_value = hash(word);
    // Access linked list at that index in hash table
    node *new_node = table[hash_value];
    // Traverse linked list, looking for word (strcasecomp)
    while (new_node != NULL)
    {
        if (strcasecmp(word, new_node->word) == 0)
        {
            return true;
        }
        new_node = new_node->next;
    }
    return false;

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash_nb = 0;
    for (int i = 0, new_node = strlen(word); i < new_node; i++)
    {
        hash_nb += word[i];
    }
    hash_nb = hash_nb % N;
    // hash_nb = round(hash_nb / strlen(word));
    return hash_nb;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char currentword[LENGTH + 1];

    FILE *dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        while (fscanf(dict, "%s", currentword) != EOF)
        {
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return 0;
            }
            strcpy(new_node->word, currentword);

            unsigned int hash_number = hash(currentword);
            // printf("%s loaded with hash: %i...\n", currentword, hash_number);
            new_node->next = table[hash_number];
            table[hash_number] = new_node;
            dict_size++;
        }
    }
    else
    {
        printf("Dict is NULL...\n");
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Scan throug hashtable to free the nodes
    for (int i = 0; i < N; i++)
    {
        node *new_node = table[i];
        // Loop through linked list
        while (new_node != NULL)
        {
            node *tmp = new_node;
            new_node = new_node->next;
            // free temp
            free(tmp);
        }
        if (new_node == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
