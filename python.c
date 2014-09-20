#ifdef __APPLE__
  #include <Python/Python.h>
#else
  #include <Python.h>
#endif

#include "include/fjk.h"

static PyObject * py_fjk_encode(PyObject *self, PyObject *args);
static PyObject * py_fjk_decode(PyObject *self, PyObject *args);

static PyMethodDef SpamMethods[] = {
    {"encode",  py_fjk_encode, METH_VARARGS, "Encode string."},
    {"decode",  py_fjk_decode, METH_VARARGS, "Decode string."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initfjk(void) {
  PyObject *m;

  m = Py_InitModule("fjk", SpamMethods);
  if (m == NULL)
      return;
}

static PyObject * py_fjk_encode(PyObject *self, PyObject *args) {
  const char *s;
  PyArg_ParseTuple(args, "s", &s);
  return Py_BuildValue("s#", fjk_encrypt(s, strlen(s)), strlen(s));
}

static PyObject * py_fjk_decode(PyObject *self, PyObject *args) {
  const char *s;
  PyArg_ParseTuple(args, "s", &s);
  return Py_BuildValue("s#", fjk_decrypt(s, strlen(s)), strlen(s));
}
