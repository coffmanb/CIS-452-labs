CC=gcc
DEBUG=gdb

PROJECT=$(shell basename $(CURDIR))
TARGET=q1.c

all: build/$(PROJECT)

build/$(PROJECT): $(TARGET)
	mkdir -p build
	$(CC) $(TARGET) -o build/$(PROJECT)

clean:
	rm -rf build

.PHONY: all clean
