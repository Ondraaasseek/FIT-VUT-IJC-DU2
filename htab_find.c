// htab_find.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_struct.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    for (struct htab_item *item = t->arr_ptr[index]; item != NULL; item = item->next) {
        if (strcmp(key, item->data->key) == 0) {
            htab_pair_t *pair = malloc(sizeof(htab_pair_t));
            if (!pair) {
                return NULL;
            }
            pair->key = item->data->key;
            pair->value = item->data->value;
            return pair;
        }
    }
    return NULL;
}