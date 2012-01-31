#include "PyDNSResourceRecord.h"
#include "PyQType.h"

PyObject * PyDNSResourceRecordType_getseters_getqtype(CPyDNSResourceRecord *self, void *closure)
{
	CPyQType* l_pQType = PyObject_New(CPyQType, &PyQTypeType);
	l_pQType->qtype = self->m_p->qtype;

	return l_pQType;
};

int PyDNSResourceRecordType_getseters_setqtype(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = -1;

	if(Py_TYPE(value) == &PyQTypeType)
	{
		CPyQType* l_pQType = (CPyQType*)value;
		self->m_p->qtype = l_pQType->qtype;

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
	return PyLong_FromLong(self->m_p->qclass);
};

int PyDNSResourceRecordType_getseters_setqclass(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->qclass = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getqname(CPyDNSResourceRecord *self, void *closure)
{
	return PyString_FromString(self->m_p->qname.c_str());
};

int PyDNSResourceRecordType_getseters_setqname(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->qname = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getcontent(CPyDNSResourceRecord *self, void *closure)
{
	return PyString_FromString(self->m_p->content.c_str());
};

int PyDNSResourceRecordType_getseters_setcontent(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->content = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getpriority(CPyDNSResourceRecord *self, void *closure)
{
	return PyLong_FromLong(self->m_p->priority);
};

int PyDNSResourceRecordType_getseters_setpriority(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->priority = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getttl(CPyDNSResourceRecord *self, void *closure)
{
	return PyLong_FromLong(self->m_p->ttl);
};

int PyDNSResourceRecordType_getseters_setttl(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->ttl = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getdomain_id(CPyDNSResourceRecord *self, void *closure)
{
	return PyLong_FromLong(self->m_p->domain_id);
};

int PyDNSResourceRecordType_getseters_setdomain_id(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->domain_id = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getlast_modified(CPyDNSResourceRecord *self, void *closure)
{
	return PyLong_FromLong(self->m_p->last_modified);
};

int PyDNSResourceRecordType_getseters_setlast_modified(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->last_modified = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDNSResourceRecordType_getseters_getd_place(CPyDNSResourceRecord *self, void *closure)
{
	return PyLong_FromLong(self->m_p->d_place);
};

int PyDNSResourceRecordType_getseters_setd_place(CPyDNSResourceRecord *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_p->d_place = (DNSResourceRecord::Place)PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
}

//-----------------------------------------------------------------------------
static PyGetSetDef PyDNSResourceRecordType_getseters[] =
{
	{"qtype", (getter)PyDNSResourceRecordType_getseters_getqtype, (setter)PyDNSResourceRecordType_getseters_setqtype, "qtype", NULL},
	{"qclass", (getter)PyDNSResourceRecordType_getseters_getqclass, (setter)PyDNSResourceRecordType_getseters_setqclass, "qclass", NULL},
	{"qname", (getter)PyDNSResourceRecordType_getseters_getqname, (setter)PyDNSResourceRecordType_getseters_setqname, "qname", NULL},
	{"content", (getter)PyDNSResourceRecordType_getseters_getcontent, (setter)PyDNSResourceRecordType_getseters_setcontent, "content", NULL},
	{"priority", (getter)PyDNSResourceRecordType_getseters_getpriority, (setter)PyDNSResourceRecordType_getseters_setpriority, "priority", NULL},
	{"ttl", (getter)PyDNSResourceRecordType_getseters_getttl, (setter)PyDNSResourceRecordType_getseters_setttl, "ttl", NULL},
	{"domain_id", (getter)PyDNSResourceRecordType_getseters_getdomain_id, (setter)PyDNSResourceRecordType_getseters_setdomain_id, "domain_id", NULL},
	{"last_modified", (getter)PyDNSResourceRecordType_getseters_getlast_modified, (setter)PyDNSResourceRecordType_getseters_setlast_modified, "last_modified", NULL},
	{"d_place", (getter)PyDNSResourceRecordType_getseters_getd_place, (setter)PyDNSResourceRecordType_getseters_setd_place, "d_place", NULL},
	{NULL}  /* Sentinel */
};

PyTypeObject PyDNSResourceRecordType =
{
	PyObject_HEAD_INIT(NULL)
	0,                                        /*ob_size*/
	"playrix.powerDNS.DNSResourceRecord",     /*tp_name*/
	sizeof(CPyDNSResourceRecord),             /*tp_basicsize*/
	0,                                        /*tp_itemsize*/
	0,                                        /*tp_dealloc*/
	0,                                        /*tp_print*/
	0,                                        /*tp_getattr*/
	0,                                        /*tp_setattr*/
	0,                                        /*tp_compare*/
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
	"DNSResourceRecord waraper",              /* tp_doc */
	0,                                        /* tp_traverse */
	0,                                        /* tp_clear */
	0,                                        /* tp_richcompare */
	0,                                        /* tp_weaklistoffset */
	0,                                        /* tp_iter */
	0,                                        /* tp_iternext */
	0,                                        /* tp_methods */
	0,                                        /* tp_members */
	PyDNSResourceRecordType_getseters         /* tp_getset */
};
