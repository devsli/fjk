from distutils.core import setup, Extension

fjk = Extension('fjk',
                    sources = ['python.c', 'encrypt.c', 'decrypt.c'])

setup (name = 'FJK-encoder',
       version = '1.0',
       description = 'Simple cipher',
       ext_modules = [fjk])
