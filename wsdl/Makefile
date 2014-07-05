#DEBUG=-g
DEBUG=
SCHEME_H_DIR=..
CC=gcc
CFLAGS=-DUSE_DL=1  -I.. $(~/sdl1.2/bin/sdl-config --cflags --static-libs)
# CFLAGS=-DUSE_DL=1 -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -I $(SCHEME_H_DIR) -L/usr/lib/x86_64-linux-gnu -lSDL -lpthread -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lX11 -lXext -L/usr/lib/x86_64-linux-gnu -lcaca -lpthread


tsx.so : wsdl.c wsdl.h Makefile
	$(CC) -shared -Wall -fPIC $(CFLAGS) -o wsdl.so $(DEBUG) wsdl.c
	strip wsdl.so
	ls -l wsdl.so

.PHONY : clean
clean:
	rm -f *.o
	rm -f wsdl.so
	rm -f *~
