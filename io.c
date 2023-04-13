// io.c
// Řešení IJC-DU2, příklad b) 13.04.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "io.h"

int read_word(char *s, int max, FILE *f) {
    int c;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) {
            if (i > 0) {
                break;
            }
        } else {
            if (i < max - 1) {
                s[i++] = c;
            } else {
                fprintf(stderr, "Warning: word too long\n");
                s[i] = '\0';
                while ((c = fgetc(f)) != EOF && !isspace(c)) {
                    continue;
                }
                break;
            }
        }
    }
    s[i] = '\0';
    return (i > 0 || c != EOF) ? i : EOF;
}