#include <pdns/qtype.hh>
#include <Python.h>

struct CPyQType: public PyObject
{
	QType qtype;
};

extern "C" PyTypeObject PyQTypeType;
