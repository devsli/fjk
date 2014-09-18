SOURCES=decrypt.c encrypt.c fjk.c
HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-Wall -Wextra -O2
EXECUTABLE=fjk

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

clean:
	rm *.o
