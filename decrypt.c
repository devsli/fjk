#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fjk.h"
#include "decrypt.h"

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
	int tail_size;
	int tail_idx;
	int chunk_size;
	int chunk_offset;
	int chunk_idx;
	int pos;

	chunk_idx = CHUNKS-1;
	chunk_offset = 0;
	result = malloc(size);
	tail_size = size % CHUNKS;
	tail_idx = tail_size - 1;
	pos = tail_size;
	chunk_size = size / CHUNKS;

	// Write tail

	while (tail_idx >= 0) {
		*(result+size-tail_idx-1) = *(encoded+tail_idx);
		--tail_idx;
	}

	// Write data

	while (pos < size) {
		*(result+(chunk_idx*chunk_size)+chunk_offset) = *(encoded+pos);
		++pos;

		if (--chunk_idx < 0) {
			chunk_idx = CHUNKS-1;
			++chunk_offset;
		}
	}

	return result;
}
