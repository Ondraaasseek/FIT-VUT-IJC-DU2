// htab_bucket_count.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_struct.h"

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}