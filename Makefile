SOURCES=decrypt.c encrypt.c fjk.c
HEADERS=include/*.h
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-Wall -Wextra -O2
EXECUTABLE=fjk

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

py-module: $(SOURCES) $(HEADERS)
	python setup.py build

clean:
	rm *.o
