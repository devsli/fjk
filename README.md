fjk-encoder
===========

Simple cipher

Command-line:

```bash
$ make

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
