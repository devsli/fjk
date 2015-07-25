fjk cipher
==========

Command-line:

```bash
$ sudo apt-get install python-dev # in case you want to build python extension
$ make

$ ./fjk -h
Usage: ./fjk [-d] [-i infile] [-o outfile] [-h]
        -d:      decrypt
        -i FILE: input file, or STDIN
        -o FILE: output file, or STDOUT
        -h:      display this help and exit

$ echo "Hello world" | ./fjk
roHl edwl
ol

$ echo "Hello world" | ./fjk | ./fjk -d
Hello world
```

Python:

```python
import fjk

print fjk.encrypt('Hello, world!')
print fjk.decrypt('!ooHr,el ldwl')
```

Contribution
============

1. fork
1. edit
1. `make test` && pull request

Cool stuff
==========
* [siu/minunit](https://github.com/siu/minunit)
