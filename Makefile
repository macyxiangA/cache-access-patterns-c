CC ?= gcc
CFLAGS ?= -std=gnu99 -Wall -Wextra -pedantic

TARGETS := cache1D cache2Drows cache2Dcols cache2Dclash

.PHONY: all run clean

all: $(TARGETS)

cache1D: cache1D.c
	$(CC) $(CFLAGS) cache1D.c -o cache1D

cache2Drows: cache2Drows.c
	$(CC) $(CFLAGS) cache2Drows.c -o cache2Drows

cache2Dcols: cache2Dcols.c
	$(CC) $(CFLAGS) cache2Dcols.c -o cache2Dcols

cache2Dclash: cache2Dclash.c
	$(CC) $(CFLAGS) cache2Dclash.c -o cache2Dclash

run: all
	./cache1D
	./cache2Drows
	./cache2Dcols
	./cache2Dclash

clean:
	rm -f $(TARGETS) *.o
