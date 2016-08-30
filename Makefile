LIBSRC=decrypt.c encrypt.c
SOURCES=$(LIBSRC) fjk.c
HEADERS=include/*.h
OBJECTS=$(SOURCES:.c=.o)
CC?=gcc
CFLAGS=-Wall -Wextra -O2 -fPIC
EXECUTABLE=fjk

all: $(EXECUTABLE) py-module

$(EXECUTABLE): $(OBJECTS)

shared: fjks

libfjk.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ decrypt.o encrypt.o

fjks: fjk.c libfjk.so
	$(CC) $(CFLAGS) -o $@ fjk.c -lfjk -L`pwd`

py-module: $(SOURCES) $(HEADERS)
	python setup.py build

clean:
	rm *.o

test:
	if [ -x ./tester ]; then rm tester; fi
	$(CC) $(CFLAGS) $(TESTFLAGS) -o tester tests/fjk_test.c $(LIBSRC)
	./tester
