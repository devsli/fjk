SRC=decrypt.c decrypt.h encrypt.c encrypt.h fjk.h fjk.c
BINDIR=bin

fjk: $(SRC)
	gcc -Wall -Wextra -O2 decrypt.c encrypt.c fjk.c -o $@

fjkdec: decrypt.c fjk.h
	gcc -O2 decrypt.c -o fjkdec


fjkenc: encrypt.c fjk.h
	gcc -O2 encrypt.c -o fjkenc
