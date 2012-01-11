#include <qtype.hh>
#include <python.h>

struct CPyQType: public PyObject
{
	QType m_p;
};

PyObject* PyQTypeType_methods_getName(CPyQType* self);
PyObject* PyQTypeType_methods_getCode(CPyQType* self);

static PyMethodDef PyDNSPacketType_methods[] =
{
	{"getName", (PyCFunction)PyQTypeType_methods_getName, METH_NOARGS, "get Requester Remote addr"},
	{"getCode", (PyCFunction)PyQTypeType_methods_getCode, METH_NOARGS, "get Requester Remote port"},
	{NULL}  /* Sentinel */
};

int PyQTypeType___init__(CPyQType *self, PyObject *args, PyObject *kwds);
int PyQTypeType___cmp__(CPyQType *self, PyObject *);

static PyTypeObject PyQTypeType =
{
    PyObject_HEAD_INIT(NULL)
    0,                                        /*ob_size*/
    "playrix.powerDNS.QType",                 /*tp_name*/
    sizeof(CPyQType),                         /*tp_basicsize*/
    0,                                        /*tp_itemsize*/
    0,                                        /*tp_dealloc*/
    0,                                        /*tp_print*/
    0,                                        /*tp_getattr*/
    0,                                        /*tp_setattr*/
    (cmpfunc)PyQTypeType___cmp__,             /*tp_compare*/
    0,                                        /*tp_repr*/
    0,                                        /*tp_as_number*/
    0,                                        /*tp_as_sequence*/
    0,                                        /*tp_as_mapping*/
    0,                                        /*tp_hash */
    0,                                        /*tp_call*/
    0,                                        /*tp_str*/
    0,                                        /*tp_getattro*/
    0,                                        /*tp_setattro*/
    0,                                        /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,                       /*tp_flags*/
    "QType waraper",                          /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    PyDNSPacketType_methods,                  /* tp_methods */
    0,                                        /*tp_members*/
    0,                                        /*tp_getset*/
    0,                                        /*tp_base*/
    0,                                        /*tp_dict*/
    0,                                        /*tp_descr_get*/
    0,                                        /*tp_descr_set*/
    0,                                        /*tp_dictoffset*/
    (initproc)PyQTypeType___init__            /*tp_init*/
};