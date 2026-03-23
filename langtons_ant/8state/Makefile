INCDIRS=-I.
CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99
LDFLAGS=-lm
SRCS=main.c pam.c
BIN=main
OBJS=$(SRCS:.c=.o)
IMG_DIR="./frames"
VID="antimation (get it hehe).mkv"

.PHONY: all clean animate

all: $(BIN)
	mkdir $(IMG_DIR)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^
clean: 
	rm $(BIN) $(OBJS)
	rm -rf $(IMG_DIR)

animate:
	ffmpeg -f image2 -i "$(IMG_DIR)/langton%05d.pam" -vf "scale=3840x2160:flags=neighbor,fps=24" -c:v libx264 -tune animation -preset ultrafast $(VID)

