#include "stdafx.h"
#include "PyQType.h"

int PyQTypeType___init__(CPyQType *self, PyObject *args, PyObject *kwds)
{
	int retval = -1;

	const char * l_sp;
	const int l_ip;
	PyObject* l_pp;

	if (PyArg_ParseTuple(args, "s", &l_sp))
	{
		self->m_p = l_sp;
		retval = 0;
	}
	else if (PyArg_ParseTuple(args, "l", &l_ip))
	{
		self->m_p = l_ip
		retval = 0;
	}
	else if(PyArg_ParseTuple(args, "O", &l_pp) && (Py_TYPE(l_pp) == &PyQTypeType))
	{
		self->m_p = ((CPyQType *)l_pp)->m_p
		retval = 0;
	}
	else
	{
		PyErr_SetString(PyExc_TypeError, "Illegal type");
	};

	return retval;
};

int PyQTypeType___cmp__(CPyQType *self, PyObject * right)
{
	int retval = -1

	if(Py_TYPE(value) == &PyQTypeType)
	{
		PyErr_SetString(PyExc_TypeError, "Illegal type");
	}
	else
	{
		CPyQType * l_right = (CPyQType *)right

		if(self->m_p == l_right->m_p)
		{
			retval = 0
		}
		else if(l_right->m_p < self->m_p)
		{
			retval = 1;
		};
	};

	return retval
};

PyObject* PyQTypeType_methods_getName(CPyQType* self)
{
	return PyString_FromString(self->m_p.getName().c_str());
};

PyObject* PyQTypeType_methods_getCode(CPyQType* self)
{
	return PyLong_FromLong(self->m_p.getCode());
};
