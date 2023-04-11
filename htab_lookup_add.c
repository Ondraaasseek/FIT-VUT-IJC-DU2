#include "htab.h"
#include <stdlib.h>

struct htab_item {
    htab_pair_t *data;
    struct htab_item *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

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

    // Check if the key already exists in the table
    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            return current->data;
        }
        current = current->next;
    }

    // Key not found in the table, create a new pair
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        return NULL; // Error allocating memory
    }

    new_item->data = malloc(sizeof(htab_pair_t));
    if (new_item->data == NULL) {
        free(new_item);
        return NULL; // Error allocating memory
    }

    new_item->data->key = strdup(key);
    new_item->data->value = 0;

    // Insert the new pair at the beginning of the linked list
    new_item->next = t->arr_ptr[index];
    t->arr_ptr[index] = new_item;

    t->size++;

    return new_item->data;
}