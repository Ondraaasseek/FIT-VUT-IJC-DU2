// htab_erase.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"

struct htab_item {
    htab_pair_t *data;
    struct htab_item *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current = t->arr_ptr[index];
    struct htab_item *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            // Našel jsem pár na smazání
            if (previous == NULL) {
                // Pár je první předmět v linked listu
                t->arr_ptr[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current->data->key);
            free(current);

            t->size--;
            return true;
        }

        previous = current;
        current = current->next;
    }

    // Pár nebyl nalezen v tablu
    return false;
}