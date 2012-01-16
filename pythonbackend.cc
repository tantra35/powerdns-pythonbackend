#include <string>
#include <sstream>

#include <pdns/misc.hh>
#include <pdns/lock.hh>

#include "pythonbackend.hh"
#include "RefCount.h"

#include "PyGILLock.h"
#include "PyDNSPacket.h"
#include "PyDNSResourceRecord.h"
#include "PyQType.h"
#include "PySOAData.h"
#include "PyDomainInfo.h"

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
pthread_mutex_t PythonBackendFactory::startup_lock;

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
PythonBackendFactory::PythonBackendFactory() : BackendFactory("python")
{
	Lock lock(&startup_lock);

	if(!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();

		//регистрация новых типов
		PyType_Ready(&PyDNSPacketType);
		PyType_Ready(&PyDNSResourceRecordType);
		PyType_Ready(&PyQTypeType);
		PyType_Ready(&PySOADataType);
		PyType_Ready(&PyDomainInfoType);

		Py_INCREF(&PyDNSPacketType);
		Py_INCREF(&PyDNSResourceRecordType);
		Py_INCREF(&PyQTypeType);
		Py_INCREF(&PySOADataType);
		Py_INCREF(&PyDomainInfoType);

		Py_InitModule("playrix", NULL);
		PyObject* l_playrix_powerDNSmodule = Py_InitModule("playrix.powerDNS", NULL);

		PyModule_AddObject(l_playrix_powerDNSmodule, "QType", (PyObject*)&PyQTypeType);
		PyModule_AddObject(l_playrix_powerDNSmodule, "SOAData", (PyObject*)&PySOADataType);
		PyModule_AddObject(l_playrix_powerDNSmodule, "DomainInfo", (PyObject*)&PyDomainInfoType);

		PyThreadState_Swap(NULL);
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
PythonBackend::PythonBackend(const string &suffix)
{
	setArgPrefix("python" + suffix);
	CPyGILLock l_pylock;

	if(!getArg("class").empty())
	{
		vector<string> l_pythonclassparts;
		stringtok(l_pythonclassparts, getArg("class"), ".");

		if(l_pythonclassparts.size() == 2)
		{
			string l_s_module = l_pythonclassparts[0];
			string l_s_class = l_pythonclassparts[1];

			RefCount<PyObject> l_py_module = PyImport_ImportModule(l_s_module.c_str());

			if(l_py_module)
			{
				RefCount<PyObject> l_py_class = PyObject_GetAttrString(l_py_module, l_s_class.c_str());

				if(l_py_class)
				{
					if(PyType_Check(l_py_class))
					{
						__m_py_object = PyObject_CallObject(l_py_class, NULL);

						if(!__m_py_object)
						{
							RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
							PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

							RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
							RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

							std::stringstream l_exeptiontextstream;
							l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

							L << Logger::Error << logprefix << "Can't instantiate class '" << l_s_class << "' due '" << l_exeptiontextstream.str() << "'" << endl;
							throw new AhuException(l_exeptiontextstream.str());
						};
					}
					else
					{
						L << Logger::Error << logprefix << l_s_class << " is not class object. or not a class of new style i.e. not derived from object" << endl;
						throw new AhuException("Wrong class config param");
					};
				}
				else
				{
					RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
					PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

					RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
					RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

					std::stringstream l_exeptiontextstream;
					l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

					L << Logger::Error << logprefix << "Can't get class '" << l_s_class << "' due '" << l_exeptiontextstream.str() << "'" << endl;
					throw new AhuException("Wrong class config param");
				};
			}
			else
			{
				RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
				PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

				RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
				RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

				std::stringstream l_exeptiontextstream;
				l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

				L << Logger::Error << logprefix << "Can't import module '" << l_s_module << "' due '" << l_exeptiontextstream.str() << "'" << endl;
				throw new AhuException("Wrong class config param");
			};
		}
		else
		{
			L << Logger::Error << logprefix << "Wrong class config param" << endl; 
			throw new AhuException("Wrong class config param");
		};
	}
	else
	{
		L << Logger::Error << logprefix << "You do not provide class config parameter" << endl; 
		throw new AhuException("You do not provide class config parameter");
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

	RefCount<CPyQType> l_pQType = PyObject_New(CPyQType, &PyQTypeType);
	l_pQType->qtype = qtype;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, (char *)"lookup", (char *)"(OsOi)", (PyObject*)l_pQType, qdomain.c_str(), (PyObject*)l_pDNSPacket, zoneId);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
		RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

		std::stringstream l_exeptiontextstream;
		l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

		L << Logger::Error << logprefix << "Can't call lookup due '" << l_exeptiontextstream.str() << "'" << endl;
		throw new DBException(l_exeptiontextstream.str());
	};
};

bool PythonBackend::list(const string &target, int domain_id)
{
	CPyGILLock l_pylock;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, (char *)"list", (char *)"(si)", target.c_str(), domain_id);

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

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, (char *)"get", (char *)"(O)", (PyObject*)l_pDNSResourceRecord);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
		RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

		std::stringstream l_exeptiontextstream;
		l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

		L << Logger::Error << logprefix << "Can't call get due '" << l_exeptiontextstream.str() << "'" << endl;
		throw new DBException(l_exeptiontextstream.str());
	};

	return PyObject_IsTrue(l_retval);
};

bool PythonBackend::getSOA(const string &name, SOAData &soadata, DNSPacket *pkt_p)
{
	CPyGILLock l_pylock;

	RefCount<CPyDNSPacket> l_pDNSPacket = PyObject_New(CPyDNSPacket, &PyDNSPacketType);
	l_pDNSPacket->m_p = pkt_p;

	RefCount<CPySOAData> l_pSOAData = PyObject_New(CPySOAData, &PySOADataType);
	l_pSOAData->psoa = &soadata;
	l_pSOAData->psoa->db = this;

	RefCount<PyObject> l_retval = PyObject_CallMethod(__m_py_object, (char *)"getSOA", (char *)"(sOO)", name.c_str(), (PyObject*)l_pSOAData, (PyObject*)l_pDNSPacket);

	if(!l_retval)
	{
		RefCount<PyObject> l_ptype, l_pvalue, l_ptraceback;
		PyErr_Fetch(&l_ptype, &l_pvalue, &l_ptraceback);

		RefCount<PyObject> ll_ptype = PyObject_Str(l_ptype);
		RefCount<PyObject> ll_pvalue = PyObject_Str(l_pvalue);

		std::stringstream l_exeptiontextstream;
		l_exeptiontextstream << PyString_AsString(ll_ptype) << " : " << PyString_AsString(ll_pvalue);

		L << Logger::Error << logprefix << "Can't call getSOA due '" << l_exeptiontextstream.str() << "'" << endl;
		throw new DBException(l_exeptiontextstream.str());
	};

	return PyObject_IsTrue(l_retval);
};
