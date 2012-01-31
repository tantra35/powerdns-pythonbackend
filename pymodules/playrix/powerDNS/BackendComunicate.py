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
  def add_domain(self, dname, ttl):
    retval = True;

    with g_rlock.writelock:
      if not dname in g_root:
        g_root[dname] = {'ttl': ttl, 'backets': {}};

      else:
        retval = False;

    return retval

  def rmv_domain(self, dname):
    retval = True;

    with g_rlock.writelock:
      if dname in g_root:
        del g_root[dname]

      else:
        retval = False;

    return retval

  def add_domain_backet(self, dname, bdname, longitude, latitude, default=False):
    retval = True;

    if len(bdname) == 3:
      with g_rlock.writelock:
        if dname in g_root:
          l_append_enable = True
          l_backets = g_root[dname]['backets'];

          if default:
            for l_bname, l_bvalue in l_backets.iteritems():
              if 'default' in l_bvalue and l_bvalue['default']:
                l_append_enable = False;
                break;

          if l_append_enable:
            l_backets[bdname] = {'longitude': longitude, 'latitude': latitude, 'ips': []};

            if default:
              l_backets[bdname]['default'] = True;

          else:
            retval = False

        else:
          retval = False

    else:
      retval = False

    return retval

  def rmv_domain_backet(self, dname, bdname):
    retval = True;

    with g_rlock.writelock:
      if dname in g_root:
        if bdname in g_root[dname]:
          del g_root[dname][bdname];

        else:
          retval = False

      else:
        retval = False

    return retval;

  def add_domain_backet_ip(self, dname, bdname, ip):
    with g_rlock.writelock:
      if not dname in g_root:
        return False;

      l_backets = g_root[dname]['backets'];

      if bdname != "LB":
        if not bdname in l_backets:
          return False;

      else:
        if not bdname in l_backets:
          l_backets[bdname] = {'ips': []};

      if not ip in l_backets[bdname]['ips']:
        l_backets[bdname]['ips'].append(ip);

      else:
        return False;

    return True

  def rmv_domain_backet_ip(self, dname, bdname, ip):
    with g_rlock.writelock:
      if not dname in g_root:
        return False;

      l_backets = g_root[dname]['backets'];

      if not bdname in l_backets:
        return False;

      if not ip in l_backets[bdname]['ips']:
        return False;

      l_backets[bdname]['ips'].remove(ip);

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
