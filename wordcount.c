// wordcount.c
// Řešení IJC-DU2, příklad a) 06.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

int main() {
    htab_t *t = htab_init(16);
    char word[128];
    while (scanf("%127s", word) == 1) {
        htab_iterator_t it = htab_lookup_add(t, word);
        it.value->data++;
    }
    for (htab_iterator_t it = htab_begin(t); !htab_iterator_equal(it, htab_end(t)); it = htab_iterator_next(it)) {
        printf("%s\t%d\n", it.ptr->key, it.ptr->data);
    }
    htab_free(t);
    return 0;
}