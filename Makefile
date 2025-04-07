CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =

SRC = main.c helpers.c options.c
OBJ = $(SRC:.c=.o)
BIN = secho

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install -Dm755 $(BIN) $(DESTDIR)/usr/bin/$(BIN)

uninstall:
	rm -f $(DESTDIR)/usr/bin/$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
