//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


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
