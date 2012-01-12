#include <string>

#include <pdns/misc.hh>
#include <pdns/lock.hh>

#include "pythonbackend.hh"
#include "RefCount.h"

#include "PyDNSPacket.h"
#include "PyDNSResourceRecord.h"
#include "PyQType.h"
#include "PySOAData.h"

PythonBackendFactory::PythonBackendFactory() : BackendFactory("python")
{
	if(!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();

		//регистрация новых типов
		PyType_Ready(&PyDNSPacketType);
		PyType_Ready(&PyDNSResourceRecordType);
		PyType_Ready(&PyQTypeType);
		PyType_Ready(&PySOADataType);

		Py_INCREF(&PyDNSPacketType);
		Py_INCREF(&PyDNSResourceRecordType);
		Py_INCREF(&PyQTypeType);
		Py_INCREF(&PySOADataType);

		PyObject* l_playrixmodule = Py_InitModule("playrix", NULL);
		PyObject* l_playrix_powerDNSmodule = Py_InitModule("playrix.powerDNS", NULL);

		PyModule_AddObject(l_playrix_powerDNSmodule, "QType", (PyObject*)&PyQTypeType);
		PyModule_AddObject(l_playrix_powerDNSmodule, "SOAData", (PyObject*)&PySOADataType);

		PyEval_ReleaseLock();
	};
};

void PythonBackendFactory::declareArguments(const string &suffix)
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
PythonBackend::PythonBackend(const string &suffix)
{
	setArgPrefix("python" + suffix);
	CPyGILLock l_pylock;

	vector<string> l_pythonclassparts;
	stringtok(l_pythonclassparts, getArg("class"), ".");

	string l_s_module = l_pythonclassparts[0];
	string l_s_class = l_pythonclassparts[1];

	RefCount<PyObject> l_py_module = PyImport_ImportModule(l_s_module.c_str());
	RefCount<PyObject> l_py_class = PyObject_GetAttrString(l_py_module, l_s_class.c_str());

	__m_py_object = PyObject_CallObject(l_py_class, NULL);

	if(!__m_py_object)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(l_pvalue);
		throw new DBException(l_exeptiontext);
	};
};

PythonBackend::~PythonBackend()
{
	CPyGILLock l_pylock;
	Py_DECREF(__m_py_object);
};

void PythonBackend::lookup(const QType &qtype, const string &qdomain, DNSPacket *pkt_p, int zoneId)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSPacket> l_pDNSPacket = PyObject_New(CPyDNSPacket, &PyDNSPacketType);
	l_pDNSPacket->m_p = pkt_p;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "lookup", "(IsOI)", qtype, qdomain.c_str(), l_pDNSPacket, zoneId);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(l_pvalue);
		throw new DBException(l_exeptiontext);
	};
};

bool PythonBackend::list(const string &target, int domain_id)
{
	CPyGILLock l_pylock;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "list", "(sI)", target.c_str(), domain_id);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(l_pvalue);
		throw new DBException(l_exeptiontext);
	};

	return PyObject_IsTrue(l_retval);
};

bool PythonBackend::get(DNSResourceRecord &r)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSResourceRecord> l_pDNSResourceRecord = PyObject_New(CPyDNSResourceRecord, &PyDNSResourceRecordType);
	l_pDNSResourceRecord->m_p = &r;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "get", "(O)", l_pDNSResourceRecord);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(l_pvalue);
		throw new DBException(l_exeptiontext);
	};

	return PyObject_IsTrue(l_retval);
};

bool PythonBackend::getSOA(const string &name, SOAData &soadata, DNSPacket *pkt_p)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSPacket> l_pDNSPacket = PyObject_New(CPyDNSPacket, &PyDNSPacketType);
	l_pDNSPacket->m_p = pkt_p;

	RefCount<CPySOAData> l_pSOAData = PyObject_New(CPySOAData, &PySOADataType);
	soadata.db = this;
	l_pSOAData->psoa = &soadata;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, "getSOA", "(sOO)", name.c_str(), l_pSOAData, l_pDNSPacket);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		std::string l_exeptiontext = PyString_AsString(l_pvalue);
		throw new DBException(l_exeptiontext);
	};

	return PyObject_IsTrue(l_retval);
};
