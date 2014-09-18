fjk-encoder
===========

Simple cipher

```bash
$ make
$ echo "Hello world" > msg.txt

$ ./fjk -i msg.txt -o encrypted.txt
$ cat encrypted.txt 
roHl edwl
ol

$ ./fjk -d -i encrypted.txt -o msg-test.txt
$ cat msg-test.txt 
Hello world
```
