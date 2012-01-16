#include "PyGILLock.h"

CPyGILLock::CPyGILLock()
{
	__m_pgstate = PyGILState_Ensure();
};

CPyGILLock::~CPyGILLock()
{
	PyGILState_Release(__m_pgstate);
};
