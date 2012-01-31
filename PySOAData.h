#include <pdns/dns.hh>
#include <Python.h>

struct CPySOAData: public PyObject
{
	SOAData* psoa;
};

extern "C" PyTypeObject PySOADataType;
