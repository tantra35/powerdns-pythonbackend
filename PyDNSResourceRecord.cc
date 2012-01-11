#include "PyDNSResourceRecord.h"

PyObject * PyDNSResourceRecordType_getseters_getqtype(CPyDNSResourceRecord *self, void *closure)
{
	CPyQType* l_pQType = PyObject_New(CPyQType, &PyQTypeType);
	l_pQType->m_p = self->m_p->qtype

	return l_pQType;
};

int PyDNSResourceRecordType_getseters_setqtype(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = -1;

	if(Py_TYPE(value) == &PyQTypeType)
	{
		CPyQType* l_pQType = (CPyQType*)value;
		self->m_p->qtype = l_pQType->m_p;

		retval = 0;
	}
	else
	{
		PyErr_SetString(PyExc_TypeError, "Illegal type");
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getqclass(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setqclass(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getqname(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setqname(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getwildcardname(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setwildcardname(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getcontent(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setcontent(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getpriority(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setpriority(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getttl(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setttl(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getdomain_id(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setdomain_id(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getlast_modified(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setlast_modified(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getd_place(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setd_place(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
}

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getauth(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setauth(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getscopeMask(CPyDNSResourceRecord *self, void *closure)
{
};

int PyDNSResourceRecordType_getseters_setscopeMask(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
};

