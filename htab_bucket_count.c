#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}