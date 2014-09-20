fjk-encoder
===========

Simple cipher

```bash
$ make

$ echo "Hello world" | ./fjk -o encrypted.txt
$ cat encrypted.txt 
roHl edwl
ol

$ ./fjk -d -i encrypted.txt -o msg-test.txt
$ cat msg-test.txt 
Hello world

$ echo Hello world | ./fjk | ./fjk -d
Hello world

```
