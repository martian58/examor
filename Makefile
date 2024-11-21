CC = gcc
CFLAGS = -Wall -I./include

SRC = src/dsaproject.c src/main.c
OBJ = $(SRC:src/%.c=build/%.o)
EXEC = main

all: create_build_dir $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

create_build_dir:
	mkdir -p build

clean:
	rm -rf build $(EXEC)
