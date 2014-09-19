#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/fjk.h"

/*
 *  input: 87531642
 *
 *   data: |8|7|5|3|1|6|4|2|
 *         +-+-+-+-+-+-+-+-+
 *   tail: | | | | | | |7|8|
 * body 1: |1|2| | | | |7|8|
 * body 2: |1|2|3|4| | |7|8|
 * body 3: |1|2|3|4|5|6|7|8|
 *
 * output: 12345678
 */

char* fjk_decrypt(const char *encoded, int size)
{
	char *result;
	int pos;
	struct tail t;
	struct chunk c;

	c.idx = CHUNK_SZ-1;
	c.offset = 0;
	result = malloc(size * sizeof(char));
	t.size = size % CHUNK_SZ;
	t.idx = t.size - 1;
	pos = t.size;
	c.count = size / CHUNK_SZ;

	// Write tail

	while (t.idx >= 0) {
		*(result+size-t.idx-1) = *(encoded+t.idx);
		--t.idx;
	}

	// Write data

	while (pos < size) {
		*(result+(c.idx*c.count)+c.offset) = *(encoded+pos);
		++pos;

		if (--c.idx < 0) {
			c.idx = CHUNK_SZ-1;
			++c.offset;
		}
	}

	return result;
}
