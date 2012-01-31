AM_CPPFLAGS=@THREADFLAGS@
EXTRA_DIST=OBJECTFILES OBJECTLIBS 

INCLUDES=-I /usr/include/python2.6

lib_LTLIBRARIES = libpythonbackend.la

libpythonbackend_la_SOURCES=pythonbackend.cc pythonbackend.hh PySOAData.cc PyQType.cc PyDNSResourceRecord.cc PyDNSPacket.cc 
libpythonbackend_la_LDFLAGS=-module -lpython2.6
