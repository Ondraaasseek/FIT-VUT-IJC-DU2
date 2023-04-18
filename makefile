# Ondřej Novotný
# LC_ALL = cs_CZ.utf8

# Compilers
CC = gcc
CXX = g++

# Flags
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -fPIC

# Targets
.PHONY: all clean zip run

all: tail wordcount wordcountDynamic comp

comp: wordcount.cc 
	$(CXX) $(CXXFLAGS) wordcount.cc -o wordcount-cpp

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

HTAB_SRCS = \
	htab_hash_function.c \
	htab_init.c \
	htab_free.c \
	htab_clear.c \
	htab_statistics.c \
	htab_size.c \
	htab_bucket_count.c \
	htab_lookup_add.c \
	htab_for_each.c
HTAB_OBJS = $(HTAB_SRCS:.c=.o)
HTAB_DYN_OBJS = $(HTAB_SRCS:.c=-dyn.o)

libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

$(LIB_TARGET): $(HTAB_DYN_OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

%-dyn.o: %.c htab.h
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

run: wordcount wordcountDynamic tail
	seq 1000000 2000000|shuf > test.txt
	./tail < test.txt
	./wordcount < test.txt
	./wordcountDynamic < test.txt
	./wordcount-cpp < test.txt
	rm test.txt

clean:
	rm -f *.o *.so *.a tail wordcount wordcountDynamic wordcount-cpp xnovot2p.zip

zip:
	zip xnovot2p.zip *.c *.cc *.h makefile