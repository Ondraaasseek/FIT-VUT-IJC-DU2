#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

size_t htab_size(const htab_t *t) {
    return t->size;
}