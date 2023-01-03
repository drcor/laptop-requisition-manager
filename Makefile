CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pedantic-errors -Wmissing-declarations -Wredundant-decls -Wfloat-equal -Wmain -Wshadow
INCLUDE = include
TEST = test
MAIN = main.c
OUTPUT = main.exe

.PHONY: all test debug clean
all: debug

debug:
	$(CC) -g $(CFLAGS) $(MAIN) $(INCLUDE)/* -o $(OUTPUT)

test:
	gcc -Wall test/*.c include/*.c -o test.exe

clean:
	rm *.exe