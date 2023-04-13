// htab_statistics.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

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

void htab_statistics(const htab_t *t) {
    size_t min = __UINT32_MAX__;
    size_t max = 0;
    size_t sum = 0;

    for (size_t i = 0; i < t->arr_size; i++) {
        size_t count = 0;
        for (struct htab_item *item = t->arr_ptr[i]; item != NULL; item = item->next) {
            count++;
        }
        if (count < min) {
            min = count;
        }
        if (count > max) {
            max = count;
        }
        sum += count;
    }

    fprintf(stderr, "Minimum length: %zu\n", min);
    fprintf(stderr, "Maximum length: %zu\n", max);
    fprintf(stderr, "Average length: %f\n", (double)sum / (double)t->arr_size);
}