// wordcount.c
// Řešení IJC-DU2, příklad b) 11.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 127  // Maximální délka slova

void print_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(void) {
    htab_t *table = htab_init(12500);  // Vytvořím HashTable s 12500 bucketama aby byl runtime programu pro seq 1000000 2000000|shuf na merlinovi 3,51 sekund
    if (table == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for the hash table.\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LENGTH + 1];                           // Buffer na čtení slov
    while (read_word(word, MAX_WORD_LENGTH, stdin) != EOF) {  // Čtu slovo jedno podruhém
        htab_pair_t *pair = htab_lookup_add(table, word);     // Zkusím najít slovo v HashTablu
        if (pair == NULL) {                                   // Chyba při pokusu o přidání slova do tablu
            fprintf(stderr, "Error: Failed to add an item to the hash table.\n");
            htab_clear(table);  // Uvolním všechny data v Tablu
            htab_free(table);   // Uvolním ten table
            return EXIT_FAILURE;
        }
        pair->value++;  // Inkrementuju count pro ten word
    }
    
    // iteruju přes všechny položky v tabulce a vypíšu je
    htab_for_each(table, print_pair);

    htab_statistics(table);  // Vypíšu statistiku ohledně tabulky

    htab_clear(table);  // Uvolním všechny data v Tablu
    htab_free(table);   // Uvolním ten table
    return EXIT_SUCCESS;
}
