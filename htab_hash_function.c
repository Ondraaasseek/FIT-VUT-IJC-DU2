// htab_hash_function.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "htab.h"

size_t htab_hash_function(htab_key_t str) { 
    __uint32_t h = 0;
    const unsigned char *p; 
    for(p = (const unsigned char*)str; *p != '\0'; p++) {
        h = 65599 * h + *p; 
    }
    return h; 
}