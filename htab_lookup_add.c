// htab_lookup_add.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_struct.h"

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d == NULL) {
        return NULL;
    }
    memcpy(d, s, len);
    return d;
}


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current = t->arr_ptr[index];

    // Kouknu jestli už je klíč v tablu
    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            return current->data;
        }
        current = current->next;
    }

    // Klíč nenalezen vytvořím nový pár
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        return NULL; // Chyba v alokaci paměti
    }

    new_item->data = malloc(sizeof(htab_pair_t));
    if (new_item->data == NULL) {
        free(new_item);
        return NULL; // Chyba v alokaci paměti
    }

    new_item->data->key = strdup(key);
    if (new_item->data->key == NULL) {
        free(new_item->data);
        free(new_item);
        return NULL; // Chyba v alokaci paměti
    }
    new_item->data->value = 0;

    // Vložím nový pár na začátek linked listu
    new_item->next = t->arr_ptr[index];
    t->arr_ptr[index] = new_item;

    t->size++;

    return new_item->data;
}