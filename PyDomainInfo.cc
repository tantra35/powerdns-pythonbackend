#include "PyDomainInfo.h"
#include "RefCount.h"

PyObject * PyDomainInfoType_getseters_getid(CPyDomainInfo *self, void *closure)
{
	return PyLong_FromLong(self->m_domaininfo->id);
};

int PyDomainInfoType_getseters_setid(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_domaininfo->id = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getzone(CPyDomainInfo *self, void *closure)
{
	return PyString_FromString(self->m_domaininfo->zone.c_str());
};

int PyDomainInfoType_getseters_setzone(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_domaininfo->zone = PyString_AsString(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getmasters(CPyDomainInfo *self, void *closure)
{
	std::vector<std::string>& l_masters = self->m_domaininfo->masters;
	std::vector<std::string>::iterator l_masters_iter;

	PyObject * l_retval = PyTuple_New(l_masters.size());
	int l_i = 0;

	for(l_masters_iter = l_masters.begin(); l_masters_iter != l_masters.end(); ++l_masters_iter, ++l_i)
	{
		PyObject * l_master = PyString_FromString((*l_masters_iter).c_str());
		PyTuple_SetItem(l_retval, l_i, l_master);
	};

	return l_retval;
};

int PyDomainInfoType_getseters_setmasters(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	RefCount<PyObject> l_pymasters = PySequence_Fast(value, "");
	std::vector<std::string> l_masters;

	if(l_pymasters)
	{
		PyObject ** ll_pymasters = PySequence_Fast_ITEMS((PyObject *)l_pymasters);
		Py_ssize_t l_pymasters_count = PySequence_Fast_GET_SIZE((PyObject *)l_pymasters);

		for(Py_ssize_t l_i = 0; l_i < l_pymasters_count; ++l_i)
		{
			RefCount<PyObject> l_pymaster = PyObject_Str(ll_pymasters[l_i]);
			l_masters.push_back(PyString_AsString(l_pymaster));
		};

		self->m_domaininfo->masters.swap(l_masters);
	}
	else
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getnotified_serial(CPyDomainInfo *self, void *closure)
{
	return PyLong_FromLong(self->m_domaininfo->notified_serial);
};

int PyDomainInfoType_getseters_setnotified_serial(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_domaininfo->notified_serial = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getserial(CPyDomainInfo *self, void *closure)
{
	return PyLong_FromLong(self->m_domaininfo->serial);
};

int PyDomainInfoType_getseters_setserial(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_domaininfo->serial = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getlast_check(CPyDomainInfo *self, void *closure)
{
	return PyLong_FromLong(self->m_domaininfo->last_check);
};

int PyDomainInfoType_getseters_setlast_check(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;
	self->m_domaininfo->last_check = PyLong_AsLong(value);

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
PyObject * PyDomainInfoType_getseters_getkind(CPyDomainInfo *self, void *closure)
{
	return PyLong_FromLong(self->m_domaininfo->kind);
};

int PyDomainInfoType_getseters_setkind(CPyDomainInfo *self, PyObject *value, void *closure)
{
	int retval = 0;

	switch(PyLong_AsLong(value))
	{
		case 0:
			self->m_domaininfo->kind = DomainInfo::Master;
		break;

		case 1:
			self->m_domaininfo->kind = DomainInfo::Slave;
		break;

		case 2:
			self->m_domaininfo->kind = DomainInfo::Native;
		break;
	};

	if(PyErr_Occurred())
	{
		retval = -1;
	};

	return retval;
};

//-----------------------------------------------------------------------------
void PyDomainInfoType_dealloc(CPyDomainInfo* self)
{
	delete self->m_domaininfo;
	self->ob_type->tp_free((PyObject*)self); 
};

int PyDomainInfoType___init__(CPyDomainInfo* self, PyObject *args, PyObject *kwds)
{
	self->m_domaininfo = new DomainInfo();
	return 0;
};

//-----------------------------------------------------------------------------
static PyGetSetDef PyDomainInfoType_getseters[] =
{
	{"id", (getter)PyDomainInfoType_getseters_getid, (setter)PyDomainInfoType_getseters_setid, "id", NULL},
	{"zone", (getter)PyDomainInfoType_getseters_getzone, (setter)PyDomainInfoType_getseters_setzone, "zone", NULL},
	{"masters", (getter)PyDomainInfoType_getseters_getmasters, (setter)PyDomainInfoType_getseters_setmasters, "masters", NULL},
	{"notified_serial", (getter)PyDomainInfoType_getseters_getnotified_serial, (setter)PyDomainInfoType_getseters_setnotified_serial, "notified_serial", NULL},
	{"serial", (getter)PyDomainInfoType_getseters_getserial, (setter)PyDomainInfoType_getseters_setserial, "serial", NULL},
	{"last_check", (getter)PyDomainInfoType_getseters_getlast_check, (setter)PyDomainInfoType_getseters_setlast_check, "last_check", NULL},
	{"kind", (getter)PyDomainInfoType_getseters_getkind, (setter)PyDomainInfoType_getseters_setkind, "kind", NULL},
	{NULL}  /* Sentinel */
};

PyTypeObject PyDomainInfoType =
{
	PyObject_HEAD_INIT(NULL)
	0,                                        /*ob_size*/
	"playrix._powerDNS.DomainInfo",           /*tp_name*/
	sizeof(CPyDomainInfo),                    /*tp_basicsize*/
	0,                                        /*tp_itemsize*/
	(destructor)PyDomainInfoType_dealloc,     /*tp_dealloc*/
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
	"DomainInfo waraper",                     /* tp_doc */
	0,                                        /* tp_traverse */
	0,                                        /* tp_clear */
	0,                                        /* tp_richcompare */
	0,                                        /* tp_weaklistoffset */
	0,                                        /* tp_iter */
	0,                                        /* tp_iternext */
	0,                                        /* tp_methods */
	0,                                        /* tp_members */
	PyDomainInfoType_getseters,               /* tp_getset */
	0,                                        /*tp_base*/
	0,                                        /*tp_dict*/
	0,                                        /*tp_descr_get*/
	0,                                        /*tp_descr_set*/
	0,                                        /*tp_dictoffset*/
	(initproc)PyDomainInfoType___init__,      /*tp_init*/
	0,                                        /* tp_alloc */
	PyType_GenericNew                         /* tp_new */
};
