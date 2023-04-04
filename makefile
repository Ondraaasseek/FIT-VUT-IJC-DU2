# Ondřej Novotný
LC_ALL = cs_CZ.utf8
Compiler = gcc
Flagy = -std=c11 -pedantic -Wall -Wextra -O2

.PHONY: all zip clean run

all: tail

tail.o: tail.c
	$(Compiler) $(Flagy) -c tail.c -o tail.o


#spustitelné binárky
tail: tail.o 
	$(Compiler) tail.o -o tail

#Final help

zip: 
	zip xnovot2p.zip *.c *.h makefile

clean:
	rm -f *.o tail xnovot2p.zip

run: tail
	./tail test.txt