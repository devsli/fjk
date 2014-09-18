#define CHUNKS 3
#define set_io(fname, stdpipe, var, fmode, errno) if (strlen(fname)) {\
  if ((var = fopen(fname, fmode)) == NULL) {\
    perror("Unable to open " #var " file"); exit(errno);\
  }\
} else { var = stdpipe; }
