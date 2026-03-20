CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99
CFILES=main.c
OBJECTS=main.o
BIN=main
IMG_DIR="./frames"
VID="antimation (get it hehe).mkv"

all: $(BIN)
	mkdir $(IMG_DIR)

$(BIN): $(OBJECTS)
	$(CC) -o  $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
animate:
	ffmpeg -f image2 -i "$(IMG_DIR)/langton%05d.pbm" -vf "scale=3840x2160:flags=neighbor,fps=24" -c:v libx264 -crf 10 -tune animation -preset veryslow $(VID)
clean:
	rm $(BIN) $(OBJECTS) 
	rm -rf $(IMG_DIR)
