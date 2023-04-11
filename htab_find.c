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