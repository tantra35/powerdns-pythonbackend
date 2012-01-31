#include "PyDNSPacket.h"

PyObject* PyDNSPacketType_methods_getRemote(CPyDNSPacket* self)
{
	return PyString_FromString(self->m_p->getRemote().c_str());
};

PyObject* PyDNSPacketType_methods_getRemotePort(CPyDNSPacket* self)
{
	return PyLong_FromLong(self->m_p->getRemotePort());
};
