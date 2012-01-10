class CPyDNSPacket: public PyObject
{
public:
	DNSPacket* __m_p;

	PyObject* getRemote()
	{
		return PyString_FromString(__m_p->getRemote().c_str());
	};

	PyObject* getRemotePort()
	{
		return PyLong_FromLong(__m_p->getRemotePort());
	};
}

static PyMethodDef PyDNSPacketType_methods[] =
{
	{"getRemote", (PyCFunction)CPyDNSPacket::getRemote, METH_NOARGS, "get Requester Remote addr"},
	{"getRemotePort", (PyCFunction)CPyDNSPacket::getRemotePort, METH_NOARGS, "get Requester Remote port"}}
	{NULL}  /* Sentinel */
};

static PyTypeObject PyDNSPacketType =
{
    PyObject_HEAD_INIT(NULL)
    0,                                        /*ob_size*/
    "playrix.powerDNS.DNSPacket",             /*tp_name*/
    sizeof(CPyDNSPacket),                     /*tp_basicsize*/
    0,                                        /*tp_itemsize*/
    NULL,                                     /*tp_dealloc*/
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
    "DNSPacket waraper",                      /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    PyDNSPacketType_methods,                  /* tp_methods */
    0,                                        /* tp_members */
};