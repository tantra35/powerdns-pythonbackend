#include <Python.h>

class CPyGILLock
{
public:
	CPyGILLock();
	~CPyGILLock();

private:
	PyGILState_STATE __m_pgstate;
};
