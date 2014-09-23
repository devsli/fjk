#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SZ 3
#define BUFF_SZ 64

#define SET_IO(var, fname, fmode) if (strlen(fname)) {  \
    if ((var = fopen(fname, fmode)) == NULL) {          \
        perror("Unable to open " #var " file");         \
        exit(errno);                                    \
    }                                                   \
}

#define UNUSED(x) (void)(x)

struct tail {
	unsigned int size;
	int idx;
};

struct chunk {
	unsigned long idx;
	int offset;
	unsigned long count;
};

typedef char* (*fjk_algo)(const char *data, size_t size);
typedef void  (*walker)(FILE *src, FILE *dst, fjk_algo method);

char* fjk_encrypt(const char *decoded, size_t size);
char* fjk_decrypt(const char *encoded, size_t size);
