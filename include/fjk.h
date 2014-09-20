#define CHUNK_SZ 3
#define BUFF_SZ 64

#define set_io(var, fname, fmode) if (strlen(fname)) {\
  if ((var = fopen(fname, fmode)) == NULL) {\
    perror("Unable to open " #var " file"); exit(errno);}}

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

char* fjk_encrypt(const char *decoded, size_t size);
char* fjk_decrypt(const char *encoded, size_t size);
