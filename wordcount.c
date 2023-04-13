// wordcount.c
// Řešení IJC-DU2, příklad b) 11.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 127  // maximum length of a word

void print_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(void) {
    clock_t start = clock();
    htab_t *table = htab_init(10000);  // create a hash table with 5000 buckets
    if (table == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for the hash table.\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LENGTH + 1];                           // buffer for reading words
    while (read_word(word, MAX_WORD_LENGTH, stdin) != EOF) {  // read one word at a time
        htab_pair_t *pair = htab_lookup_add(table, word);     // try to find the word in the table
        if (pair == NULL) {                                   // error while adding a new item
            fprintf(stderr, "Error: Failed to add an item to the hash table.\n");
            htab_clear(table);  // free all the items in the table
            htab_free(table);   // free the table itself
            return EXIT_FAILURE;
        }
        pair->value++;  // increment the count for this word
    }
    printf("Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    // iterate over all the items in the table and print them
    // htab_for_each(table, print_pair);

    htab_statistics(table);  // print statistics about the hash table

    htab_clear(table);  // free all the items in the table
    htab_free(table);   // free the table itself
    return EXIT_SUCCESS;
}
