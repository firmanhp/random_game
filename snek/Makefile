CC = g++
OUT = out

CCFLAGS = -std=c++20 -I./ -Wextra -Wthread-safety -fsanitize=undefined
LIBFLAGS = -lncurses
TARGET = snek
SRC = food.cc game.cc main.cc snake.cc world.cc
OBJ = $(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) $(LIBFLAGS) -o $@ $^

%.o : %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean