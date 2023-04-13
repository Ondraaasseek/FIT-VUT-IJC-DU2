#include <stdlib.h>

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