#include <string>

#include <pdns/misc.hh>
#include <pdns/lock.hh>

#include "pythonbackend.hh"
#include "PyDNSPacket.h"
#include "RefCount.h"

PythonBackendFactory::PythonBackendFactory() : BackendFactory("python")
{
	if(!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();

		//регистрация нового типа
		PyType_Ready(&PyDNSPacketType);

		PyEval_ReleaseLock();
	};
};

void PythonBackendFactory::declareArguments(const string &suffix = "")
{
	declare(suffix, "class", "python class to serve dns querys", "");
};

DNSBackend* PythonBackendFactory::make(const string &suffix)
{
	return new PythonBackend(suffix);
};

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
class CPyGILLock
{
public:
	CPyGILLock()
	{
		PyEval_AcquireLock();
	};

	~CPyGILLock()
	{
		PyEval_ReleaseLock();
	}
};

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
PythonBackend::PythonBackend()
{
	CPyGILLock l_pylock;

	vector<string> l_pythonclassparts;
	stringtok(l_pythonclassparts, getArg("class"), ".");

	string l_s_module = l_pythonclassparts[0];
	string l_s_class = l_pythonclassparts[1];

	RefCount<PyObject> l_py_module = PyImport_ImportModule(l_s_module.c_str());
	RefCount<PyObject> l_py_class = PyObject_GetAttrString(l_py_module, l_s_class.c_str());

	__m_py_object = PyObject_CallObject(l_py_class, NULL, NULL);

	if(!__m_py_object)
	{
		RefCount<PyObject> l_ptype, *l_pvalue, *l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(pvalue);
		throw new DBException(l_exeptiontext);
	};
};

PythonBackend::~PythonBackend()
{
	CPyGILLock l_pylock;
	Py_DECREF(__m_py_object);
};

void PythonBackend::lookup(const QType &qtype, const string &qdomain, DNSPacket *pkt_p=0, int zoneId=-1)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSPacket> l_pDNSPacket = PyObject_New(CPyDNSPacket, &PyDNSPacketType);
	l_pDNSPacket->m_p = pkt_p

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "lookup", "(IsOI)", qtype, qdomain.c_str(), l_pDNSPacket, zoneId);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, *l_pvalue, *l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(pvalue);
		throw new DBException(l_exeptiontext);
	};
};

bool PythonBackend::list(const string &target, int domain_id)
{
	CPyGILLock l_pylock;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "list", "(sI)", target.c_str(), domain_id);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, *l_pvalue, *l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(pvalue);
		throw new DBException(l_exeptiontext);
	};
};

bool PythonBackend::get(DNSResourceRecord &r)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSResourceRecord> l_pDNSResourceRecord = PyObject_New(CPyDNSResourceRecord, &PyDNSResourceRecordType);
	l_pDNSResourceRecord->m_p = &r;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "get", "(O)", l_pDNSResourceRecord);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, *l_pvalue, *l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(pvalue);
		throw new DBException(l_exeptiontext);
	};

	return retval;
};
