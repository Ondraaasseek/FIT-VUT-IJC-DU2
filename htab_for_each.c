#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

struct htab_item {
    htab_pair_t *data;
    struct htab_item *next;
};

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        for (struct htab_item *item = t->arr_ptr[i]; item != NULL; item = item->next) {
            htab_pair_t pair = {item->data->key, item->data->value};
            f(&pair);
        }
    }
}