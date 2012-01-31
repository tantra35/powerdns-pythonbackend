AM_CPPFLAGS=@THREADFLAGS@
EXTRA_DIST=OBJECTFILES OBJECTLIBS

INCLUDES=-I/usr/include/python2.6 -I/home/ruslan/pystring

lib_LTLIBRARIES = libpythonbackend.la

libpythonbackend_la_SOURCES=pythonbackend.cc pythonbackend.hh PyGILLock.cc PySOAData.cc PyQType.cc PyDNSResourceRecord.cc PyDNSPacket.cc PyDomainInfo.cc
libpythonbackend_la_LDFLAGS=-module -lpython2.6 /home/ruslan/pystring/.libs/libpystring.a
libpythonbackend_la_CPPFLAGS=-fno-strict-aliasing -fPIC
