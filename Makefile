SOURCES=decrypt.c encrypt.c fjk.c
HEADERS=include/*.h
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-Wall -Wextra -O2
EXECUTABLE=fjk

all: $(EXECUTABLE) py-module fjks

$(EXECUTABLE): $(OBJECTS)

libfjk.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ decrypt.o encrypt.o

fjks: fjk.c libfjk.so
	$(CC) $(CFLAGS) -o $@ fjk.c -lfjk -L`pwd`

py-module: $(SOURCES) $(HEADERS)
	python setup.py build

clean:
	rm *.o
