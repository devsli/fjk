//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fjk.h"
#include "encrypt.h"
#include "decrypt.h"

void print_usage(char *selfname);
void run(char *from, char *to, int decrypt);

int main(int argc, char **argv)
{
	int inset = 0, outset = 0, dec = 0;
	int opt;
	char *infile;
	char *outfile;
	
	while((opt = getopt(argc, argv, "di:o:")) != -1) {
		switch (opt) {
		case 'd':
			dec = 1;
			break;
		case 'i':
			infile = optarg;
			inset = 1;
			break;
		case 'o':
			outfile = optarg;
			outset = 1;
			break;
		default:
			print_usage(argv[0]);
			exit(1);
		}
	}
	if (inset && outset) {
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
	int size;

	if ((file = fopen(from, "rb")) == NULL) {
		printf("Unable to open file %s\n", from);
		exit(2);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	indat = malloc(size+1);
	assert(size == fread(indat, 1, size, file));
	fclose(file);

	if (dec) {
		outdat = decrypt(indat, size);
	} else {
		outdat = encrypt(indat, size);
	}

	if ((file = fopen(to, "wb")) == NULL) {
		printf("Unable to open file %s\n", to);
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
