#ifdef __APPLE__
  #include <Python/Python.h>
#else
  #include <Python.h>
#endif

#include "include/fjk.h"

static PyObject* py_fjk_encode(PyObject *self, PyObject *args);
static PyObject* py_fjk_decode(PyObject *self, PyObject *args);

static PyMethodDef FjkMethods[] = {
    {"encode",  py_fjk_encode, METH_VARARGS, "Encode string."},
    {"decode",  py_fjk_decode, METH_VARARGS, "Decode string."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initfjk(void) {
  PyObject *m;

  m = Py_InitModule("fjk", FjkMethods);
  if (m == NULL)
      return;
}

PyObject* _py_fjk_wrap(PyObject *args, fjk_algo method) {
  const char *s;
  if (!PyArg_ParseTuple(args, "s", &s))
    return NULL;
  return Py_BuildValue("s#", method(s, strlen(s)), strlen(s));
}

static PyObject* py_fjk_encode(PyObject *self, PyObject *args) {
  return _py_fjk_wrap(args, fjk_encrypt);
}

static PyObject* py_fjk_decode(PyObject *self, PyObject *args) {
  return _py_fjk_wrap(args, fjk_decrypt);
}
