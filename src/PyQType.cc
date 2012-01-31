#include "PyQType.h"

int PyQTypeType___init__(CPyQType *self, PyObject *args, PyObject *kwds)
{
	int retval = -1;
	PyObject* l_pp;

	if(PyArg_ParseTuple(args, "O", &l_pp))
	{
		if(PyNumber_Check(l_pp))
		{
			self->qtype = PyLong_AsLong(l_pp);
			retval = 0;
		}
		else if(PyString_Check(l_pp))
		{
			self->qtype = PyString_AsString(l_pp);
			retval = 0;
		}
		else if(PyObject_IsInstance(l_pp, (PyObject *)&PyQTypeType))
		{
			self->qtype = ((CPyQType *)l_pp)->qtype;
			retval = 0;
		}
		else
		{
			PyErr_SetString(PyExc_TypeError, "Illegal type");
		};
	};

	return retval;
};

PyObject* PyQTypeType___repr__(CPyQType *self)
{
	return PyString_FromString(self->qtype.getName().c_str());
};

int PyQTypeType___cmp__(CPyQType *self, PyObject * right)
{
	int retval = -1;

	CPyQType * l_right = (CPyQType *)right;

	if(self->qtype == l_right->qtype)
	{
		retval = 0;
	}
	else if(l_right->qtype < self->qtype)
	{
		retval = 1;
	};

	return retval;
};

PyObject* PyQTypeType_methods_getName(CPyQType* self)
{
	return PyString_FromString(self->qtype.getName().c_str());
};

PyObject* PyQTypeType_methods_getCode(CPyQType* self)
{
	return PyLong_FromLong(self->qtype.getCode());
};

static PyMethodDef PyQTypeType_methods[] =
{
	{"getName", (PyCFunction)PyQTypeType_methods_getName, METH_NOARGS, "get Requester Remote addr"},
	{"getCode", (PyCFunction)PyQTypeType_methods_getCode, METH_NOARGS, "get Requester Remote port"},
	{NULL}  /* Sentinel */
};

PyTypeObject PyQTypeType =
{
    PyObject_HEAD_INIT(NULL)
    0,                                        /*ob_size*/
    "playrix._powerDNS._QType",               /*tp_name*/
    sizeof(CPyQType),                         /*tp_basicsize*/
    0,                                        /*tp_itemsize*/
    0,                                        /*tp_dealloc*/
    0,                                        /*tp_print*/
    0,                                        /*tp_getattr*/
    0,                                        /*tp_setattr*/
    (cmpfunc)PyQTypeType___cmp__,             /*tp_compare*/
    (reprfunc)PyQTypeType___repr__,           /*tp_repr*/
    0,                                        /*tp_as_number*/
    0,                                        /*tp_as_sequence*/
    0,                                        /*tp_as_mapping*/
    0,                                        /*tp_hash */
    0,                                        /*tp_call*/
    (reprfunc)PyQTypeType___repr__,           /*tp_str*/
    0,                                        /*tp_getattro*/
    0,                                        /*tp_setattro*/
    0,                                        /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "QType waraper",                          /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    PyQTypeType_methods,                      /* tp_methods */
    0,                                        /*tp_members*/
    0,                                        /*tp_getset*/
    0,                                        /*tp_base*/
    0,                                        /*tp_dict*/
    0,                                        /*tp_descr_get*/
    0,                                        /*tp_descr_set*/
    0,                                        /*tp_dictoffset*/
    (initproc)PyQTypeType___init__,           /*tp_init*/
    0,                                        /* tp_alloc */
    PyType_GenericNew                         /* tp_new */
};
