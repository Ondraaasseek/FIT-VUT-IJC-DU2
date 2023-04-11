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

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *current = t->arr_ptr[i];
        while (current != NULL) {
            struct htab_item *next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}