#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <ctype.h>

/*
čte jedno slovo ze souboru f do zadaného pole znaků
a vrátí délku slova (z delších slov načte prvních max-1 znaků,
a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
*/
int read_word(char *s, int max, FILE *f);

#endif