SRC = $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

ARGS = test
BINDIR = bin/
BINARY = $(BINDIR)cursesart

CFLAGS = -Wall -g --pedantic --std=c90 -I include
LFLAGS = -l ncurses

CC = gcc


all: $(BINARY)
	
$(BINARY): $(OBJ) | bin
	$(CC) $(CFLAGS) $(OBJ) -o $(BINARY) $(LFLAGS)

obj/%.o: src/%.c | obj
	$(CC) -MD $(CFLAGS) $< -o $@ -c

-include obj/*.d

obj:
	@mkdir obj

bin:
	@mkdir bin

run: $(BINARY)
	./$(BINARY) $(ARGS)

.PHONY=clean
clean:
	rm -f $(BINARY) $(OBJ) obj/*.d
	