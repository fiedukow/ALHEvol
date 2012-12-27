# Copyright (C) 2006  Ralph dos Santos Silva
#LIBDIR = /home/rsilva1/local/libsun
LIBDIR = /usr/lib
INCLUDEDIR = /usr/include

LIBGSL = -lgsl
LIBCBLAS = -lgslcblas
LIBATLAS = -latlas
LIBMATH = -lm

CFLAGS = -O2 -std=gnu99 -static -g -Wall -W -DHAVE_INLINE -I$(INCLUDEDIR)

CC = gcc

.c.o:
	$(CC) $(CFLAGS) -c $<

all: test.o rmv.o 
	$(CC) -o test test.o rmv.o -L$(LIBDIR) $(LIBGSL) $(LIBCBLAS) $(LIBATLAS) $(LIBMATH) 

clean:
	rm -f *.o test
