#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fjk.h"
#include "decrypt.h"

char* decrypt(const char *encoded, int size)
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
