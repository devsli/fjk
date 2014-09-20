#define CHUNK_SZ 3
#define BUFF_SZ 64

#define set_io(var, fname, fmode) if (strlen(fname)) {\
  if ((var = fopen(fname, fmode)) == NULL) {\
    perror("Unable to open " #var " file"); exit(errno);}}

struct tail {
	int size;
	int idx;
};

struct chunk {
	int idx;
	int offset;
	int count;
};

typedef char* (*fjk_algo)(const char *data, int size);

char* fjk_encrypt(const char *decoded, int size);
char* fjk_decrypt(const char *encoded, int size);
