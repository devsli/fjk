#define CHUNKS 3
#define set_io(var, fname, stdpipe, fmode, errno) if (strlen(fname)) {\
  if ((var = fopen(fname, fmode)) == NULL) {\
    perror("Unable to open " #var " file"); exit(errno);\
  }\
} else { var = stdpipe; }

char* fjk_encrypt(const char *decoded, int size);
char* fjk_decrypt(const char *encoded, int size);
