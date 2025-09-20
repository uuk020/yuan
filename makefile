CC = gcc

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -g -std=c99 -Wall -Wextra
else
	CFLAGS = -O2 -std=c99 -Wall -Wextra
endif

TARGET = yuan

SRCS = $(wildcard ./src/*.c)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Compiling and linking..."
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
