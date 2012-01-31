#include <Python.h>
#include <pdns/dns.hh>

struct CPyDNSResourceRecord: public PyObject
{
	DNSResourceRecord* m_p;
};

extern "C" PyTypeObject PyDNSResourceRecordType;
