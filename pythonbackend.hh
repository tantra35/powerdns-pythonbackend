/*        geobackend.hh
 *        	Copyright (C) 2004 Mark Bergsma <mark@nedworks.org>
 *        	This software is licensed under the terms of the GPL, version 2.
 * 
 *        	$Id: geobackend.hh 2324 2011-12-23 17:40:53Z peter $
 */
#include <pdns/dnsbackend.hh>
#include <pdns/logger.hh>

#include <pthread.h>
#include <Python.h>

const static string logprefix = "[pythonbackend] "; 

class PythonBackend : public DNSBackend
{
public:
	PythonBackend(const string &suffix);
	~PythonBackend();

	virtual void lookup(const QType &qtype, const string &qdomain, DNSPacket *pkt_p=0, int zoneId=-1);
	virtual bool list(const string &target, int domain_id);
	virtual bool get(DNSResourceRecord &r);
	virtual bool getSOA(const string &name, SOAData &soadata, DNSPacket *p=0);

private:
	PyObject* __m_py_object;
};

class PythonBackendFactory : public BackendFactory
{
public:
	PythonBackendFactory();
	void declareArguments(const string &suffix = "");
	DNSBackend *make(const string &suffix);

private:
	static pthread_mutex_t startup_lock;
};

class PythonBackendLoader
{
public:
	PythonBackendLoader()
	{
		BackendMakers().report(new PythonBackendFactory());
		L << Logger::Info << logprefix << "This is the pythonbackend ("__DATE__", "__TIME__" - $Revision: 1.1 $) reporting" << endl;
	};
};

static PythonBackendLoader pythonloader;
