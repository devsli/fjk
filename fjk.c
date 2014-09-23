#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include "include/fjk.h"

void print_usage(char *selfname);
void memrun(FILE *from, FILE *to, fjk_algo method);
void swapper(FILE *from, FILE *to, fjk_algo _);

int main(int argc, char **argv)
{
	int opt;
	extern int errno;
	fjk_algo method = &fjk_encrypt;
	walker run = &memrun;
	FILE *input = stdin, *output = stdout;

	while((opt = getopt(argc, argv, "hdsi:o:")) != -1) {
		switch (opt) {
		case 'd':
			method = &fjk_decrypt;
			break;
		case 's':
			run = &swapper;
			break;
		case 'i':
			SET_IO(input,  optarg, "rb");
			break;
		case 'o':
			SET_IO(output, optarg, "wb");
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

void memrun(FILE *from, FILE *to, fjk_algo method)
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

void swapper(FILE *from, FILE *to, fjk_algo alg)
{
	UNUSED(alg);

	char buffer[2];
	char tmp;
	while(!feof(from)) {
		if (fread(buffer, sizeof(char), 2, from) == 1) {
			fwrite(buffer, sizeof(char), 1, to);
		} else {
			tmp = buffer[0];
			buffer[0] = buffer[1];
			buffer[1] = tmp;

			fwrite(buffer, sizeof(char), 2, to);
		}
	}
}

void print_usage(char *selfname)
{
	printf("Usage: %s [-d] [-s] [-i infile] [-o outfile]\n", selfname);
	printf("	-d: decrypt\n");
	printf("	-s: swap bytes\n");
	printf("	-i FILE: input file, or STDIN\n");
	printf("	-o FILE: output file, or STDOUT\n");
}
