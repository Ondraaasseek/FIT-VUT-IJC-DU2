// htab.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include <stdlib.h>
#include "htab.h"

#define HTAB_INITIAL_SIZE 16

struct htab_item {
    htab_pair_t *data;
    struct htab_item *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

size_t htab_hash_function(htab_key_t str) { 
    __uint32_t h = 0;
    const unsigned char *p; 
    for(p = (const unsigned char*)str; *p != '\0'; p++) {
        h = 65599 * h + *p; 
    }
    return h; 
}

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

size_t htab_size(const htab_t *t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}

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

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d == NULL) {
        return NULL;
    }
    memcpy(d, s, len);
    return d;
}


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current = t->arr_ptr[index];

    // Kouknu jestli už je klíč v tablu
    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            return current->data;
        }
        current = current->next;
    }

    // Klíč nenalezen vytvořím nový pár
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        return NULL; // Chyba v alokaci paměti
    }

    new_item->data = malloc(sizeof(htab_pair_t));
    if (new_item->data == NULL) {
        free(new_item);
        return NULL; // Chyba v alokaci paměti
    }

    new_item->data->key = strdup(key);
    if (new_item->data->key == NULL) {
        free(new_item->data);
        free(new_item);
        return NULL; // Chyba v alokaci paměti
    }
    new_item->data->value = 0;

    // Vložím nový pár na začátek linked listu
    new_item->next = t->arr_ptr[index];
    t->arr_ptr[index] = new_item;

    t->size++;

    return new_item->data;
}

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current = t->arr_ptr[index];
    struct htab_item *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            // Našel jsem pár na smazání
            if (previous == NULL) {
                // Pár je první předmět v linked listu
                t->arr_ptr[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current->data);
            free(current);

            t->size--;
            return true;
        }

        previous = current;
        current = current->next;
    }

    // Pár nebyl nalezen v tablu
    return false;
}

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        for (struct htab_item *item = t->arr_ptr[i]; item != NULL; item = item->next) {
            htab_pair_t pair = {item->data->key, item->data->value};
            f(&pair);
        }
    }
}

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *current = t->arr_ptr[i];
        while (current != NULL) {
            htab_pair_t *data = current->data;
            free((void *)data->key);
            free(data);
            current->data = NULL;
            struct htab_item *temp = current;
            current = current->next;
            free(temp);
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}

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