#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/fjk.h"
#include "include/encrypt.h"

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
	int tail_size;
	int tail_idx;
	int chunk_offset;
	int chunk_count;
	int chunk_idx;
	int pos;

	result = malloc(size);
	tail_size = size % CHUNKS;
	tail_idx = tail_size - 1;
	pos = 0;

	chunk_count = size / CHUNKS;
	chunk_idx = 0;
	chunk_offset = CHUNKS - 1;

	// Write tail

	while (tail_idx >= 0) {
		*(result+tail_idx) = *(decoded+size-tail_idx-1);
		--tail_idx;
	}

	// Write data

	while (pos+tail_size < size) {
		*(result+tail_size+(chunk_idx*CHUNKS)+chunk_offset) = *(decoded+pos);
		++pos;
		if (++chunk_idx >= chunk_count) {
			chunk_idx = 0;
			chunk_offset--;
		}
	}

	return result;
}
