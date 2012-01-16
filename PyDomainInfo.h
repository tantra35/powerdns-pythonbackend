#include <Python.h>
#include <pdns/dnsbackend.hh>

struct CPyDomainInfo: public PyObject
{
	DomainInfo* m_domaininfo;
};

extern "C" PyTypeObject PyDomainInfoType;
