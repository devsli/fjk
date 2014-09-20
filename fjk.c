#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/fjk.h"

void print_usage(char *selfname);
void run(FILE *from, FILE *to, fjk_algo method);

int main(int argc, char **argv)
{
	int opt;
	extern int errno;
	fjk_algo method = &fjk_encrypt;
	FILE *input = stdin, *output = stdout;

	while((opt = getopt(argc, argv, "hdi:o:")) != -1) {
		switch (opt) {
		case 'd':
			method = &fjk_decrypt;
			break;
		case 'i':
			set_io(input,  optarg, "rb");
			break;
		case 'o':
			set_io(output, optarg, "wb");
			break;
		case 'h':
		default:
			print_usage(argv[0]);
			exit(1);
		}
	}

	run(input, output, method);
	return 0;
}

void run(FILE *from, FILE *to, fjk_algo method)
{
	char *indat;
	char *outdat;
	size_t buffsize = BUFF_SZ;
	size_t size = 0;

	assert((indat = malloc(buffsize)) != NULL);
	size += fread(indat, sizeof(char), buffsize, from);

	while (size == buffsize) {
		buffsize = buffsize << 1;
		assert((indat = realloc(indat, buffsize)) != NULL);
		size += fread((indat + size), sizeof(char), buffsize >> 1, from);
	}
	fclose(from);

	fwrite((outdat = method(indat, size)), sizeof(char), size, to);
	fclose(to);

	free(indat);
	free(outdat);
}

void print_usage(char *selfname)
{
	printf("Usage: %s [-d] [-i infile] [-o outfile]\n", selfname);
	printf("	-d: decrypt\n");
	printf("	-i FILE: input file, or STDIN\n");
	printf("	-o FILE: output file, or STDOUT\n");
}
