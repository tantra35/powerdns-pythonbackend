import threading;
import traceback;

from contextlib import contextmanager;

from thrift.transport import TSocket;
from thrift.server import TNonblockingServer;
from thrift.protocol import TBinaryProtocol;

from playrix.powerDNS import BackendComunicateProxy;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class __ReadWriteLock:
  """A lock object that allows many simultaneous "read-locks", but
  only one "write-lock"."""

  def __init__(self):
    self._read_ready = threading.Condition(threading.Lock())
    self._readers = 0

  def acquire_read(self):
    """Acquire a read-lock. Blocks only if some thread has
    acquired write-lock."""
    self._read_ready.acquire()

    try:
      self._readers += 1

    finally:
      self._read_ready.release()

  def release_read(self):
    """Release a read-lock."""
    self._read_ready.acquire()

    try:
      self._readers -= 1

      if not self._readers:
        self._read_ready.notifyAll()

    finally:
      self._read_ready.release()

  def acquire_write(self):
    """Acquire a write lock. Blocks until there are no
    acquired read- or write-locks."""
    self._read_ready.acquire()

    while self._readers > 0:
      self._read_ready.wait()

  def release_write(self):
    """Release a write-lock."""
    self._read_ready.release()

  @property
  @contextmanager
  def readlock(self):
    self.acquire_read()

    try:
      yield

    finally:
      self.release_read()

  @property
  @contextmanager
  def writelock(self):
    self.acquire_write()

    try:
      yield

    finally:
      self.release_write()

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
g_rlock = __ReadWriteLock()
g_root = {};

class __PyBackendComunicate(threading.Thread):
  def add_backet(self, dname, bdname, longitude, latitude, ttl, default=False):
    retval = True;

    with g_rlock.writelock:
      if not dname in g_root:
        g_root[dname] = {};

      l_append_enable = True

      if default:
        for l_bname, l_bvalue in g_root[dname].iteritems():
          if 'default' in l_bvalue and l_bvalue['default']:
            l_append_enable = False;
            break;

      if l_append_enable:
        g_root[dname][bdname] = {'longitude': longitude, 'latitude': latitude, 'ips': [], 'ttl': ttl};

        if default:
          g_root[dname][bdname]['default'] = True;

      else:
        retval = False

    return retval

  def add_backet_ip(self, dname, bdname, ip):
    with g_rlock.writelock:
      if not dname in g_root:
        return False;

      if not bdname in g_root[dname]:
        return False;

      if not ip in g_root[dname][bdname]['ips']:
        g_root[dname][bdname]['ips'].append(ip);

      else:
        return False;

    return True

  def run(self):
    try:
      transport = TSocket.TServerSocket("localhost", 9160);
      pfactory = TBinaryProtocol.TBinaryProtocolAcceleratedFactory()

      server = TNonblockingServer.TNonblockingServer(BackendComunicateProxy.Processor(self), transport, pfactory)
      server.serve()

    except Exception as e:
      logging.error(traceback.format_exc());

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
__backendcomunicate = __PyBackendComunicate();
__backendcomunicate.start();
