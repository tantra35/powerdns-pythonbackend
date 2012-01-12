#include <Python.h>
#include <pdns/dnspacket.hh>

struct CPyDNSPacket: public PyObject
{
	DNSPacket* m_p;
};

extern "C" PyTypeObject PyDNSPacketType;
