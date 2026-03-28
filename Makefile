CC=gcc
CFLAGS=-Wall
LIBS=-lcrypto

all:
	$(CC) hasher-cli.c -o hasher-cli $(LIBS)

clean:
	rm -f hasher-cli
