#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/fjk.h"

/*
 *  input: 12345678
 *
 * column: |1|2|3|4|5|6|7|8|
 *         +-+-+-+-+-+-+-+-+
 *   tail: |8|7| | | | | | |
 * body 1: |8|7| | |1| | |2|
 * body 2: |8|7| |3|1| |4|2|
 * body 3: |8|7|5|3|1|6|4|2|
 *
 * output: 87531642
 */

char* fjk_encrypt(const char *decoded, int size)
{
	char *result;
	int pos;
	struct tail t;
	struct chunk c;

	result = malloc(size * sizeof(char));
	t.size = size % CHUNK_SZ;
	t.idx = t.size - 1;
	pos = 0;

	c.count = size / CHUNK_SZ;
	c.idx = 0;
	c.offset = CHUNK_SZ - 1;

	// Write tail

	while (t.idx >= 0) {
		*(result + t.idx) = *(decoded + size - t.idx-1);
		--t.idx;
	}

	// Write data

	while (pos+t.size < size) {
		*(result + t.size + (c.idx * CHUNK_SZ) + c.offset) = *(decoded + pos);
		++pos;
		if (++c.idx >= c.count) {
			c.idx = 0;
			c.offset--;
		}
	}

	return result;
}
