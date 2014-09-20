#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/fjk.h"

void print_usage(char *selfname);
void run(FILE *from, FILE *to, int decrypt);

int main(int argc, char **argv)
{
	int dec = 0;
	int opt;
	char *infile = "", *outfile = "";
	extern int errno;
	FILE *input, *output;

	while((opt = getopt(argc, argv, "di:o:")) != -1) {
		switch (opt) {
		case 'd':
			dec = 1;
			break;
		case 'i':
			infile = optarg;
			break;
		case 'o':
			outfile = optarg;
			break;
		default:
			print_usage(argv[0]);
			exit(1);
		}
	}

	set_io(input,  infile,  stdin,  "rb");
	set_io(output, outfile, stdout, "wb");

	run(input, output, dec);
	return 0;
}

void run(FILE *from, FILE *to, int dec)
{
	char *indat;
	char *outdat;
	size_t buffsize = BUFF_SZ;
	size_t size = 0;

	indat = malloc(buffsize * sizeof(char));
	size += fread(indat, sizeof(char), buffsize, from);

	while (size == buffsize) {
		buffsize = buffsize << 1;
		indat = realloc(indat, buffsize * sizeof(char));
		size += fread((indat + size), sizeof(char), buffsize >> 1, from);
	}

	fclose(from);

	if (dec) {
		outdat = fjk_decrypt(indat, size);
	} else {
		outdat = fjk_encrypt(indat, size);
	}

	fwrite(outdat, sizeof(char), size, to);
	fclose(to);

	free(indat);
	free(outdat);
}

void print_usage(char *selfname)
{
	printf("Usage: %s [-d] -i infile -o outfile\n", selfname);
	printf("	-d: decrypt\n");
}
