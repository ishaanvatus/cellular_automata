CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99
CFILES=main.c
OBJECTS=main.o
BIN=main
IMGS=*.pbm
VID=langton.mkv
all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) -o  $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
animate:
	ffmpeg -f image2 -i "langton%05d.pbm" -vf "scale=1920x1080:flags=neighbor,fps=24" -c:v libx264 -tune animation -preset ultrafast $(VID)
clean:
	rm $(BIN) $(OBJECTS) $(IMGS) $(VID)
