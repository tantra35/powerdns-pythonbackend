#include "PySOAData.h"

PyObject * PySOADataType_getseters_getqname(CPySOAData *self, void *closure)
{
	return PyString_FromString(self->psoa->qname.c_str());
};

int PySOADataType_getseters_setqname(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->qname = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getnameserver(CPySOAData *self, void *closure)
{
	return PyString_FromString(self->psoa->nameserver.c_str());
};

int PySOADataType_getseters_setnameserver(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->nameserver = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_gethostmaster(CPySOAData *self, void *closure)
{
	return PyString_FromString(self->psoa->hostmaster.c_str());
};

int PySOADataType_getseters_sethostmaster(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->hostmaster = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getttl(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->ttl);
};

int PySOADataType_getseters_setttl(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->ttl = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getserial(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->serial);
};

int PySOADataType_getseters_setserial(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->serial = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getrefresh(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->refresh);
};

int PySOADataType_getseters_setrefresh(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->refresh = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getretry(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->retry);
};

int PySOADataType_getseters_setretry(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->retry = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getexpire(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->expire);
};

int PySOADataType_getseters_setexpire(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->expire = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getdefault_ttl(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->default_ttl);
};

int PySOADataType_getseters_setdefault_ttl(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->default_ttl = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PySOADataType_getseters_getdomain_id(CPySOAData *self, void *closure)
{
	return PyLong_FromLong(self->psoa->domain_id);
};

int PySOADataType_getseters_setdomain_id(CPySOAData *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->psoa->domain_id = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
static PyGetSetDef PySOADataType_getseters[] =
{
	{"qname", (getter)PySOADataType_getseters_getqname, (setter)PySOADataType_getseters_setqname, "qname", NULL},
	{"nameserver", (getter)PySOADataType_getseters_getnameserver, (setter)PySOADataType_getseters_setnameserver, "nameserver", NULL},
	{"hostmaster", (getter)PySOADataType_getseters_gethostmaster, (setter)PySOADataType_getseters_sethostmaster, "hostmaster", NULL},
	{"ttl", (getter)PySOADataType_getseters_getttl, (setter)PySOADataType_getseters_setttl, "ttl", NULL},
	{"serial", (getter)PySOADataType_getseters_getserial, (setter)PySOADataType_getseters_setserial, "serial", NULL},
	{"refresh", (getter)PySOADataType_getseters_getrefresh, (setter)PySOADataType_getseters_setrefresh, "refresh", NULL},
	{"retry", (getter)PySOADataType_getseters_getretry, (setter)PySOADataType_getseters_setretry, "retry", NULL},
	{"expire", (getter)PySOADataType_getseters_getexpire, (setter)PySOADataType_getseters_setexpire, "expire", NULL},
	{"default_ttl", (getter)PySOADataType_getseters_getdefault_ttl, (setter)PySOADataType_getseters_setdefault_ttl, "default_ttl", NULL},
	{"domain_id", (getter)PySOADataType_getseters_getdomain_id, (setter)PySOADataType_getseters_setdomain_id, "domain_id", NULL},
	{NULL}  /* Sentinel */
};

PyTypeObject PySOADataType =
{
	PyObject_HEAD_INIT(NULL)
	0,                                        /*ob_size*/
	"playrix.powerDNS.SOAData",               /*tp_name*/
	sizeof(CPySOAData),                       /*tp_basicsize*/
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
	"SOAData waraper",                        /* tp_doc */
	0,                                        /* tp_traverse */
	0,                                        /* tp_clear */
	0,                                        /* tp_richcompare */
	0,                                        /* tp_weaklistoffset */
	0,                                        /* tp_iter */
	0,                                        /* tp_iternext */
	0,                                        /* tp_methods */
	0,                                        /* tp_members */
	PySOADataType_getseters                   /* tp_getset */
};
