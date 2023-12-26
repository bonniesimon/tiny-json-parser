# the compiler to use
CC = gcc

# compiler flags:
# -g flags for debugging
# -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -Wextra -pedantic

# the name to use for both the target source file and the output file
TARGET = src/main
EXE_DIR = bin/tiny
ADD_FILES = $(filter-out src/main.c, $(wildcard src/*.c))

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) ${CFLAGS} ${TARGET}.c ${ADD_FILES} -o $(EXE_DIR)
	./${EXE_DIR} example/sample.json

.PHONY: clean

clean:
	rm -f $(EXE_DIR)
