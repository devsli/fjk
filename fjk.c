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

	set_io(infile,   stdin,  input, "rb", 2)
	set_io(outfile, stdout, output, "wb", 3)

	run(input, output, dec);
	return 0;
}

void run(FILE *from, FILE *to, int dec)
{
	char *indat;
	char *outdat;
	long int size;

	fseek(from, 0, SEEK_END);
	assert((size = ftell(from)) != -1);
	fseek(from, 0, SEEK_SET);

	indat = malloc(size+1);
	assert((size_t) size == fread(indat, 1, size, from));
	fclose(from);

	if (dec) {
		outdat = fjk_decrypt(indat, size);
	} else {
		outdat = fjk_encrypt(indat, size);
	}

	fwrite(outdat, 1, size, to);
	fclose(to);

	free(indat);
	free(outdat);
}

void print_usage(char *selfname)
{
	printf("Usage: %s [-d] -i infile -o outfile\n", selfname);
	printf("	-d: decrypt\n");
}
