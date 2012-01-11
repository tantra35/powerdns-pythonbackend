#include <python.h>

struct CPyDNSResourceRecord: public PyObject
{
	DNSResourceRecord* m_p;
};

PyObject * PyDNSResourceRecordType_getseters_getqtype(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setqtype(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getqclass(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setqclass(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getqname(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setqname(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getwildcardname(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setwildcardname(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getcontent(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setcontent(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getpriority(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setpriority(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getttl(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setttl(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getdomain_id(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setdomain_id(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getlast_modified(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setlast_modified(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getd_place(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setd_place(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getauth(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setauth(CPyDNSResourceRecord *self, PyObject *value, void *closure);

PyObject * PyDNSResourceRecordType_getseters_getscopeMask(CPyDNSResourceRecord *self, void *closure);
int yDNSResourceRecordType_getseters_setscopeMask(CPyDNSResourceRecord *self, PyObject *value, void *closure);

static PyGetSetDef PyDNSResourceRecordType_getseters[] =
{
	{"qtype", (getter)PyDNSResourceRecordType_getseters_getqtype, (setter)PyDNSResourceRecordType_getseters_setqtype, "qtype", NULL},
	{"qclass", (getter)PyDNSResourceRecordType_getseters_getqclass, (setter)PyDNSResourceRecordType_getseters_setqclass, "qclass", NULL},
	{"qname", (getter)PyDNSResourceRecordType_getseters_getqname, (setter)PyDNSResourceRecordType_getseters_setqname, "qname", NULL},
	{"wildcardname", (getter)PyDNSResourceRecordType_getseters_getwildcardname, (setter)PyDNSResourceRecordType_getseters_setwildcardname, "wildcardname", NULL},
	{"content", (getter)PyDNSResourceRecordType_getseters_getcontent, (setter)PyDNSResourceRecordType_getseters_setcontent, "content", NULL},
	{"priority", (getter)PyDNSResourceRecordType_getseters_getpriority, (setter)PyDNSResourceRecordType_getseters_setpriority, "priority", NULL},
	{"ttl", (getter)PyDNSResourceRecordType_getseters_getttl, (setter)PyDNSResourceRecordType_getseters_setttl, "ttl", NULL},
	{"domain_id", (getter)PyDNSResourceRecordType_getseters_getdomain_id, (setter)PyDNSResourceRecordType_getseters_setdomain_id, "domain_id", NULL},
	{"last_modified", (getter)PyDNSResourceRecordType_getseters_getlast_modified, (setter)PyDNSResourceRecordType_getseters_setlast_modified, "last_modified", NULL},
	{"d_place", (getter)PyDNSResourceRecordType_getseters_getd_place, (setter)PyDNSResourceRecordType_getseters_setd_place, "d_place", NULL},
	{"auth", (getter)PyDNSResourceRecordType_getseters_getauth, (setter)PyDNSResourceRecordType_getseters_setauth, "auth", NULL},
	{"scopeMask", (getter)PyDNSResourceRecordType_getseters_getscopeMask, (setter)PyDNSResourceRecordType_getseters_setscopeMask, "scopeMask", NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject PyDNSResourceRecordType =
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
