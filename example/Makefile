#DEBUG=-g
DEBUG=
SCHEME_H_DIR=..
CC=gcc
CFLAGS=-DUSE_DL=1 -I $(SCHEME_H_DIR)

tsx.so : moddy.c moddy.h Makefile
	$(CC) -shared -Wall -fPIC $(CFLAGS) -o moddy.so $(DEBUG) moddy.c
	strip moddy.so
	ls -l moddy.so

.PHONY : clean
clean:
	rm -f *.o
	rm -f moddy.so
	rm -f *~
