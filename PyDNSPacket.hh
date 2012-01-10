class CPyDNSPacket: public PyObject
{
	DNSPacket* __m_p;

	CPyDNSPacket(DNSPacket* p)
	{
		__m_p = p
	}

	~CPyDNSPacket()
	{
	}
}

static PyMethodDef PyDNSPacketType_methods[] =
{
	{"name", (PyCFunction)Noddy_name, METH_NOARGS, "Return the name, combining the first and last name"},
	{NULL}  /* Sentinel */
};

static PyTypeObject PyDNSPacketType =
{
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "playrix.powerDNS.DNSPacket", /*tp_name*/
    sizeof(CPyDNSPacket),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Noddy_dealloc,                /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Noddy objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    PyDNSPacketType_methods,       /* tp_methods */
    0,                             /* tp_members */
    0,                             /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Noddy_init,      /* tp_init */
    0,                         /* tp_alloc */
    Noddy_new,                 /* tp_new */
};