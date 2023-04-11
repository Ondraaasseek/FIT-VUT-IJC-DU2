#include "htab.h"
#include <stdlib.h>

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}