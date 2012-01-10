#include <string>

#include <pdns/misc.hh>
#include <pdns/lock.hh>

PythonBackend::PythonBackend()
{
	if(!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();
	};

	PyEval_AcquireLock();

	vector<string> l_pythonclassparts;
	stringtok(l_pythonclassparts, getArg("class"), ".");

	string l_s_module = l_pythonclassparts[0];
	string l_s_class = l_pythonclassparts[1];

	PyObject* l_py_module = PyImport_ImportModule(l_s_module.c_str());
	PyObject* l_py_class = PyObject_GetAttrString(l_py_module, l_s_class.c_str());

	__m_py_object = PyInstance_New(l_py_class, NULL, NULL);

	Py_XDECREF(l_py_module);
	Py_XDECREF(l_py_class);

	PyEval_ReleaseLock();
};

PythonBackend::~PythonBackend()
{
	PyEval_AcquireLock();

	Py_DECREF(__m_py_object);

	PyEval_ReleaseLock();
};