CC = g++
OUT = out

CCFLAGS = -std=c++20 -I./ -Wextra -Wthread-safety -fsanitize=undefined
LIBFLAGS = -lncurses
TARGET = titres
SRC = game.cc main.cc player_piece.cc world.cc
OBJ = $(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) $(LIBFLAGS) -o $@ $^

%.o : %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean