// wordcount.c
// Řešení IJC-DU2, příklad b) 11.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 127 // maximum length of a word

void print_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(void) {
    htab_t *table = htab_init(500); // create a hash table with 500 buckets
    if (table == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for the hash table.\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LENGTH + 1]; // buffer for reading words
    while(read_word(word, MAX_WORD_LENGTH, stdin) != EOF) { // read one word at a time, up to 127 characters
        htab_pair_t *pair = htab_lookup_add(table, word); // try to find the word in the table
        if (pair == NULL) { // error while adding a new item
            fprintf(stderr, "Error: Failed to add an item to the hash table.\n");
            htab_clear(table); // free all the items in the table
            htab_free(table); // free the table itself
            return EXIT_FAILURE;
        }
        pair->value++; // increment the count for this word
    }

    // iterate over all the items in the table and print them
    htab_for_each(table, print_pair);

    htab_statistics(table); // print statistics about the hash table

    htab_clear(table); // free all the items in the table
    htab_free(table); // free the table itself

    return EXIT_SUCCESS;
}