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

char* fjk_decrypt(const char *encoded, size_t size)
{
	char *result;
	size_t current, enc_offset, dec_offset;
	struct tail t;
	struct chunk c;

	c.idx = CHUNK_SZ - 1;
	c.offset = 0;
	result = malloc(size);
	t.size = size % CHUNK_SZ;
	t.idx = t.size - 1;
	current = t.size;
	c.count = size / CHUNK_SZ;

	// Write tail

	while (t.idx >= 0) {
		dec_offset = size - t.idx - 1;
		enc_offset = t.idx--;

		*(result + dec_offset) = *(encoded + enc_offset);
	}

	// Write data

	while (current < size) {
		dec_offset = c.offset + c.idx * c.count;
		enc_offset = current;

		*(result + dec_offset) = *(encoded + enc_offset);

		current += 1;

		if (!c.idx--) {
			c.idx = CHUNK_SZ - 1;
			c.offset += 1;
		}
	}

	return result;
}
