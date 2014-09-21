#ifdef __APPLE__
  #include <Python/Python.h>
#else
  #include <Python.h>
#endif

#include "include/fjk.h"


PyObject* _py_fjk_wrap(PyObject *args, fjk_algo method) {
  const char *s;
  if (!PyArg_ParseTuple(args, "s", &s))
    return NULL;
  return Py_BuildValue("s#", method(s, strlen(s)), strlen(s));
}

static PyObject* py_fjk_encrypt(PyObject *self, PyObject *args) {
  return _py_fjk_wrap(args, fjk_encrypt);
}

static PyObject* py_fjk_decrypt(PyObject *self, PyObject *args) {
  return _py_fjk_wrap(args, fjk_decrypt);
}

static PyMethodDef FjkMethods[] = {
    {"encrypt",  py_fjk_encrypt, METH_VARARGS, "Encrypt string."},
    {"decrypt",  py_fjk_decrypt, METH_VARARGS, "Decrypt string."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initfjk(void) {
  PyObject *m;

  m = Py_InitModule("fjk", FjkMethods);
  if (m == NULL)
      return;
}
