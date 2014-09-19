#define CHUNK_SZ 3

#define set_io(var, fname, stdpipe, fmode, errno) if (strlen(fname)) {\
  if ((var = fopen(fname, fmode)) == NULL) {\
    perror("Unable to open " #var " file"); exit(errno);\
  }\
} else { var = stdpipe; }

struct tail {
	int size;
	int idx;
};

struct chunk {
	int idx;
	int offset;
	int count;
};

char* fjk_encrypt(const char *decoded, int size);
char* fjk_decrypt(const char *encoded, int size);
