#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fjk.h"
#include "encrypt.h"
#include "decrypt.h"

void print_usage(char *selfname);
void run(char *from, char *to, int decrypt);

int main(int argc, char **argv)
{
	int dec = 0;
	int opt;
	char *infile = "", *outfile = "";

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
	if (strlen(infile) && strlen(outfile)) {
		run(infile, outfile, dec);
	} else {
		print_usage(argv[0]);
		exit(1);
	}
	return 0;
}

void run(char *from, char *to, int dec)
{
	FILE *file;
	char *indat;
	char *outdat;
	long int size;

	if ((file = fopen(from, "rb")) == NULL) {
		perror("Unable to open input file");
		exit(2);
	}

	fseek(file, 0, SEEK_END);
	assert((size = ftell(file)) != -1);
	fseek(file, 0, SEEK_SET);

	indat = malloc(size+1);
	assert((size_t) size == fread(indat, 1, size, file));
	fclose(file);

	if (dec) {
		outdat = fjk_decrypt(indat, size);
	} else {
		outdat = fjk_encrypt(indat, size);
	}

	if ((file = fopen(to, "wb")) == NULL) {
		perror("Unable to open output file");
		exit(3);
	}

	fwrite(outdat, 1, size, file);
	fclose(file);

	free(indat);
	free(outdat);
}

void print_usage(char *selfname)
{
	printf("Usage: %s [-d] -i infile -o outfile\n", selfname);
	printf("	-d: decrypt\n");
}
