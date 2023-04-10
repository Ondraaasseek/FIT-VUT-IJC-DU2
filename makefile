# Ondřej Novotný
LC_ALL = cs_CZ.utf8
Compiler = gcc
Flagy = -std=c11 -pedantic -Wall -Wextra -O2

.PHONY: all zip clean run

all: tail wordcount

tail.o: tail.c
	$(Compiler) $(Flagy) -c tail.c -o tail.o

wordcount.o: wordcount.c
	$(Compiler) $(Flagy) -c wordcount.c -o wordcount.o

#spustitelné binárky
tail: tail.o 
	$(Compiler) tail.o -o tail

wordcount: wordcount.O2
	$(Compiler) wordcount.o -o wordcount

#Final help

zip: 
	zip xnovot2p.zip *.c *.h makefile

clean:
	rm -f *.o tail wordcount xnovot2p.zip

run: tail
	./tail test.txt
	./wordcount < test.txt