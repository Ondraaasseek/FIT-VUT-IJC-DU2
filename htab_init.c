// htab_init.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include <stdlib.h>
#define HTAB_INITIAL_SIZE 16

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

htab_t *htab_init(const size_t n) {
    htab_t *t = malloc(sizeof(htab_t));
    if (!t) {
        return NULL;
    }
    t->arr_size = n ? n : HTAB_INITIAL_SIZE;
    t->size = 0;
    t->arr_ptr = calloc(t->arr_size, sizeof(struct htab_item*));
    if (!t->arr_ptr) {
        free(t);
        return NULL;
    }
    return t;
}