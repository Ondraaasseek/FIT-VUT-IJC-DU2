// htab_clear.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_struct.h"

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *current = t->arr_ptr[i];
        while (current != NULL) {
            htab_pair_t *data = current->data;
            free((void *)data->key);
            free(data);
            current->data = NULL;
            struct htab_item *temp = current;
            current = current->next;
            free(temp);
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}