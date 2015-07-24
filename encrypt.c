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

char* fjk_encrypt(const char *decoded, size_t size)
{
	char *result;
	int pos;
	unsigned int enc_offset, dec_offset;
	struct tail t;
	struct chunk c;

	result = malloc(size);
	t.size = size % CHUNK_SZ;
	t.idx = t.size - 1;
	pos = 0;

	c.count = size / CHUNK_SZ;
	c.idx = 0;
	c.offset = CHUNK_SZ - 1;

	// Write tail

	while (t.idx >= 0) {
		enc_offset = t.idx;
		dec_offset = size - t.idx - 1;

		*(result + enc_offset) = *(decoded + dec_offset);

		t.idx -= 1;
	}

	// Write data

	while (pos + t.size < size) {
		enc_offset = t.size + c.offset + c.idx * CHUNK_SZ;
		dec_offset = pos;

		*(result + enc_offset) = *(decoded + dec_offset);

		pos += 1;

		if (++c.idx >= c.count) {
			c.idx = 0;
			c.offset -= 1;
		}
	}

	return result;
}
