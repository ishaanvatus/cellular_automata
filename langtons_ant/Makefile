CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99
CFILES=main.c
OBJECTS=main.o
BIN=main
IMGS=*.pbm

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) -o  $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
clean:
	rm $(BIN) $(OBJECTS) $(IMGS)
