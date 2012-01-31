#include <python.h>

struct CPyDNSPacket: public PyObject
{
	DNSPacket* m_p;
};

PyObject* PyDNSPacketType_methods_getRemote(CPyDNSPacket* self);
PyObject* PyDNSPacketType_methods_getRemotePort(CPyDNSPacket* self);

static PyMethodDef PyDNSPacketType_methods[] =
{
	{"getRemote", (PyCFunction)PyDNSPacketType_methods_getRemote, METH_NOARGS, "get Requester Remote addr"},
	{"getRemotePort", (PyCFunction)PyDNSPacketType_methods_getRemotePort, METH_NOARGS, "get Requester Remote port"},
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
    Py_TPFLAGS_DEFAULT,                       /*tp_flags*/
    "DNSPacket waraper",                      /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    PyDNSPacketType_methods,                  /* tp_methods */
};