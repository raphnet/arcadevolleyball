CC=gcc
CFLAGS=`pkg-config --cflags libpng`
LDFLAGS=`pkg-config --libs libpng`

all: extsprites


extsprites: extsprites.c
	$(CC) $(CFLAGS) extsprites.c -o extsprites $(LDFLAGS)
