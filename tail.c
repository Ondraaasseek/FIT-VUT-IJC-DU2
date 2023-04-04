// tail.c
// Řešení IJC-DU2, příklad a) 31.03.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 4095

/*  # Struktura CircularBuffer která slouží k načtení jednotlivých řádků.
*   buffer - pointer na pole znaků.
*   start a konec - značí první a poslední element.
*   size - totální kapacita bufferu.
*   count - aktuální počet stringů v bufferu.    
*/
typedef struct {
    char **buffer;
    int start;
    int end;
    int size;
    int count;
} CircularBuffer;

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d == NULL) {
        return NULL;
    }
    memcpy(d, s, len);
    return d;
}

CircularBuffer *cb_create(int n) {
    CircularBuffer *cb = (CircularBuffer *) malloc(sizeof(CircularBuffer));
    if (cb == NULL) return NULL;
    cb->buffer = (char **) malloc(n * sizeof(char *));
    if (cb->buffer == NULL) {
        free(cb);
        return NULL;
    }
    cb->start = 0;
    cb->end = -1;
    cb->size = n;
    cb->count = 0;
    return cb;
}

void cb_put(CircularBuffer *cb, char *line) {
    if (cb->count == cb->size) {
        free(cb->buffer[cb->start]);
        cb->start = (cb->start + 1) % cb->size;
        cb->count--;
    }
    cb->end = (cb->end + 1) % cb->size;
    cb->buffer[cb->end] = strdup(line);
    cb->count++;
}

char *cb_get(CircularBuffer *cb, int index) {
    if (index < 0 || index >= cb->count) return NULL;
    return cb->buffer[(cb->start + index) % cb->size];
}

void cb_free(CircularBuffer *cb) {
    for (int i = 0; i < cb->count; i++) {
        free(cb->buffer[(cb->start + i) % cb->size]);
    }
    free(cb->buffer);
    free(cb);
}

int main(int argc, char **argv) {
    int n = 10;
    FILE *fp = stdin;
    char line[MAX_LINE_LEN + 2]; // extra space for \n and \0

    // parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            n = atoi(argv[i + 1]);
            i++;
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Cannot open file %s\n", argv[i]);
                exit(1);
            }
        }
    }

    // create circular buffer
    CircularBuffer *cb = cb_create(n);
    if (cb == NULL) {
        fprintf(stderr, "Cannot create circular buffer\n");
        exit(1);
    }

    // read lines and put them into circular buffer
    while (fgets(line, MAX_LINE_LEN + 2, fp) != NULL) {
        if (strlen(line) > MAX_LINE_LEN) {
            fprintf(stderr, "Line too long: %s\n", line);
            line[MAX_LINE_LEN] = '\n';
            line[MAX_LINE_LEN + 1] = '\0';
        }
        cb_put(cb, line);
    }

    // print last n lines from circular buffer
    for (int i = 0; i < n && i < cb->count; i++) {
        printf("%s", cb_get(cb, i));
    }

    // free buffer a zavřít file
    cb_free(cb);
    if (fp != stdin) fclose(fp);

    return 0;
}