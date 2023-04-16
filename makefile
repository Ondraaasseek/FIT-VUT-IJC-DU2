# Ondřej Novotný
LC_ALL = cs_CZ.utf8

# Compilers
CC = gcc
CXX = g++

# Flags
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -fPIC

# Targets
.PHONY: all clean run

all: tail wordcount wordcountDynamic

tail: tail.o io.o
	$(CC) -o $@ $^

wordcount: wordcount.o io.o libhtab.a
	$(CC) -o $@ $^ $(CFLAGS)

wordcountDynamic: wordcount.o io.o $(LIB_TARGET)
	$(CC) -o $@ $^ $(CFLAGS) -L. -lhtab

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $< -o $@

# HTAB library

libhtab.a: htab.o
	ar rcs $@ $^

$(LIB_TARGET): htab-dyn.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

htab-dyn.o: htab.c htab.h
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

clean:
	rm -f *.o *.so *.a tail wordcount wordcountDynamic xnovot2p.zip

run: tail wordcount wordcountDynamic
	seq 1000000 2000000|shuf > test.txt
	./tail test.txt
	./wordcount < test.txt

zip:
	zip xnovot2p.zip *.c *.h makefile