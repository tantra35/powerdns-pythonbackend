#
# Autogenerated by Thrift Compiler (0.8.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py:new_style
#

from thrift.Thrift import TType, TMessageType, TException
from thrift.Thrift import TProcessor
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol, TProtocol
try:
  from thrift.protocol import fastbinary
except:
  fastbinary = None


class Iface(object):
  def add_backet(self, dname, bdname, longitude, latitude, ttl, isdefault):
    """
    Parameters:
     - dname
     - bdname
     - longitude
     - latitude
     - ttl
     - isdefault
    """
    pass

  def add_backet_ip(self, dname, bdname, ip):
    """
    Parameters:
     - dname
     - bdname
     - ip
    """
    pass

  def rmv_backet_ip(self, dname, bdname, ip):
    """
    Parameters:
     - dname
     - bdname
     - ip
    """
    pass


class Client(Iface):
  def __init__(self, iprot, oprot=None):
    self._iprot = self._oprot = iprot
    if oprot is not None:
      self._oprot = oprot
    self._seqid = 0

  def add_backet(self, dname, bdname, longitude, latitude, ttl, isdefault):
    """
    Parameters:
     - dname
     - bdname
     - longitude
     - latitude
     - ttl
     - isdefault
    """
    self.send_add_backet(dname, bdname, longitude, latitude, ttl, isdefault)
    return self.recv_add_backet()

  def send_add_backet(self, dname, bdname, longitude, latitude, ttl, isdefault):
    self._oprot.writeMessageBegin('add_backet', TMessageType.CALL, self._seqid)
    args = add_backet_args()
    args.dname = dname
    args.bdname = bdname
    args.longitude = longitude
    args.latitude = latitude
    args.ttl = ttl
    args.isdefault = isdefault
    args.write(self._oprot)
    self._oprot.writeMessageEnd()
    self._oprot.trans.flush()

  def recv_add_backet(self, ):
    (fname, mtype, rseqid) = self._iprot.readMessageBegin()
    if mtype == TMessageType.EXCEPTION:
      x = TApplicationException()
      x.read(self._iprot)
      self._iprot.readMessageEnd()
      raise x
    result = add_backet_result()
    result.read(self._iprot)
    self._iprot.readMessageEnd()
    if result.success is not None:
      return result.success
    raise TApplicationException(TApplicationException.MISSING_RESULT, "add_backet failed: unknown result");

  def add_backet_ip(self, dname, bdname, ip):
    """
    Parameters:
     - dname
     - bdname
     - ip
    """
    self.send_add_backet_ip(dname, bdname, ip)
    return self.recv_add_backet_ip()

  def send_add_backet_ip(self, dname, bdname, ip):
    self._oprot.writeMessageBegin('add_backet_ip', TMessageType.CALL, self._seqid)
    args = add_backet_ip_args()
    args.dname = dname
    args.bdname = bdname
    args.ip = ip
    args.write(self._oprot)
    self._oprot.writeMessageEnd()
    self._oprot.trans.flush()

  def recv_add_backet_ip(self, ):
    (fname, mtype, rseqid) = self._iprot.readMessageBegin()
    if mtype == TMessageType.EXCEPTION:
      x = TApplicationException()
      x.read(self._iprot)
      self._iprot.readMessageEnd()
      raise x
    result = add_backet_ip_result()
    result.read(self._iprot)
    self._iprot.readMessageEnd()
    if result.success is not None:
      return result.success
    raise TApplicationException(TApplicationException.MISSING_RESULT, "add_backet_ip failed: unknown result");

  def rmv_backet_ip(self, dname, bdname, ip):
    """
    Parameters:
     - dname
     - bdname
     - ip
    """
    self.send_rmv_backet_ip(dname, bdname, ip)
    return self.recv_rmv_backet_ip()

  def send_rmv_backet_ip(self, dname, bdname, ip):
    self._oprot.writeMessageBegin('rmv_backet_ip', TMessageType.CALL, self._seqid)
    args = rmv_backet_ip_args()
    args.dname = dname
    args.bdname = bdname
    args.ip = ip
    args.write(self._oprot)
    self._oprot.writeMessageEnd()
    self._oprot.trans.flush()

  def recv_rmv_backet_ip(self, ):
    (fname, mtype, rseqid) = self._iprot.readMessageBegin()
    if mtype == TMessageType.EXCEPTION:
      x = TApplicationException()
      x.read(self._iprot)
      self._iprot.readMessageEnd()
      raise x
    result = rmv_backet_ip_result()
    result.read(self._iprot)
    self._iprot.readMessageEnd()
    if result.success is not None:
      return result.success
    raise TApplicationException(TApplicationException.MISSING_RESULT, "rmv_backet_ip failed: unknown result");


class Processor(Iface, TProcessor):
  def __init__(self, handler):
    self._handler = handler
    self._processMap = {}
    self._processMap["add_backet"] = Processor.process_add_backet
    self._processMap["add_backet_ip"] = Processor.process_add_backet_ip
    self._processMap["rmv_backet_ip"] = Processor.process_rmv_backet_ip

  def process(self, iprot, oprot):
    (name, type, seqid) = iprot.readMessageBegin()
    if name not in self._processMap:
      iprot.skip(TType.STRUCT)
      iprot.readMessageEnd()
      x = TApplicationException(TApplicationException.UNKNOWN_METHOD, 'Unknown function %s' % (name))
      oprot.writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
      x.write(oprot)
      oprot.writeMessageEnd()
      oprot.trans.flush()
      return
    else:
      self._processMap[name](self, seqid, iprot, oprot)
    return True

  def process_add_backet(self, seqid, iprot, oprot):
    args = add_backet_args()
    args.read(iprot)
    iprot.readMessageEnd()
    result = add_backet_result()
    result.success = self._handler.add_backet(args.dname, args.bdname, args.longitude, args.latitude, args.ttl, args.isdefault)
    oprot.writeMessageBegin("add_backet", TMessageType.REPLY, seqid)
    result.write(oprot)
    oprot.writeMessageEnd()
    oprot.trans.flush()

  def process_add_backet_ip(self, seqid, iprot, oprot):
    args = add_backet_ip_args()
    args.read(iprot)
    iprot.readMessageEnd()
    result = add_backet_ip_result()
    result.success = self._handler.add_backet_ip(args.dname, args.bdname, args.ip)
    oprot.writeMessageBegin("add_backet_ip", TMessageType.REPLY, seqid)
    result.write(oprot)
    oprot.writeMessageEnd()
    oprot.trans.flush()

  def process_rmv_backet_ip(self, seqid, iprot, oprot):
    args = rmv_backet_ip_args()
    args.read(iprot)
    iprot.readMessageEnd()
    result = rmv_backet_ip_result()
    result.success = self._handler.rmv_backet_ip(args.dname, args.bdname, args.ip)
    oprot.writeMessageBegin("rmv_backet_ip", TMessageType.REPLY, seqid)
    result.write(oprot)
    oprot.writeMessageEnd()
    oprot.trans.flush()


# HELPER FUNCTIONS AND STRUCTURES

class add_backet_args(object):
  """
  Attributes:
   - dname
   - bdname
   - longitude
   - latitude
   - ttl
   - isdefault
  """

  thrift_spec = (
    None, # 0
    (1, TType.STRING, 'dname', None, None, ), # 1
    (2, TType.STRING, 'bdname', None, None, ), # 2
    (3, TType.DOUBLE, 'longitude', None, None, ), # 3
    (4, TType.DOUBLE, 'latitude', None, None, ), # 4
    (5, TType.I32, 'ttl', None, None, ), # 5
    (6, TType.BOOL, 'isdefault', None, False, ), # 6
  )

  def __init__(self, dname=None, bdname=None, longitude=None, latitude=None, ttl=None, isdefault=thrift_spec[6][4],):
    self.dname = dname
    self.bdname = bdname
    self.longitude = longitude
    self.latitude = latitude
    self.ttl = ttl
    self.isdefault = isdefault

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 1:
        if ftype == TType.STRING:
          self.dname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 2:
        if ftype == TType.STRING:
          self.bdname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 3:
        if ftype == TType.DOUBLE:
          self.longitude = iprot.readDouble();
        else:
          iprot.skip(ftype)
      elif fid == 4:
        if ftype == TType.DOUBLE:
          self.latitude = iprot.readDouble();
        else:
          iprot.skip(ftype)
      elif fid == 5:
        if ftype == TType.I32:
          self.ttl = iprot.readI32();
        else:
          iprot.skip(ftype)
      elif fid == 6:
        if ftype == TType.BOOL:
          self.isdefault = iprot.readBool();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('add_backet_args')
    if self.dname is not None:
      oprot.writeFieldBegin('dname', TType.STRING, 1)
      oprot.writeString(self.dname)
      oprot.writeFieldEnd()
    if self.bdname is not None:
      oprot.writeFieldBegin('bdname', TType.STRING, 2)
      oprot.writeString(self.bdname)
      oprot.writeFieldEnd()
    if self.longitude is not None:
      oprot.writeFieldBegin('longitude', TType.DOUBLE, 3)
      oprot.writeDouble(self.longitude)
      oprot.writeFieldEnd()
    if self.latitude is not None:
      oprot.writeFieldBegin('latitude', TType.DOUBLE, 4)
      oprot.writeDouble(self.latitude)
      oprot.writeFieldEnd()
    if self.ttl is not None:
      oprot.writeFieldBegin('ttl', TType.I32, 5)
      oprot.writeI32(self.ttl)
      oprot.writeFieldEnd()
    if self.isdefault is not None:
      oprot.writeFieldBegin('isdefault', TType.BOOL, 6)
      oprot.writeBool(self.isdefault)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

class add_backet_result(object):
  """
  Attributes:
   - success
  """

  thrift_spec = (
    (0, TType.BOOL, 'success', None, None, ), # 0
  )

  def __init__(self, success=None,):
    self.success = success

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 0:
        if ftype == TType.BOOL:
          self.success = iprot.readBool();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('add_backet_result')
    if self.success is not None:
      oprot.writeFieldBegin('success', TType.BOOL, 0)
      oprot.writeBool(self.success)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

class add_backet_ip_args(object):
  """
  Attributes:
   - dname
   - bdname
   - ip
  """

  thrift_spec = (
    None, # 0
    (1, TType.STRING, 'dname', None, None, ), # 1
    (2, TType.STRING, 'bdname', None, None, ), # 2
    (3, TType.STRING, 'ip', None, None, ), # 3
  )

  def __init__(self, dname=None, bdname=None, ip=None,):
    self.dname = dname
    self.bdname = bdname
    self.ip = ip

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 1:
        if ftype == TType.STRING:
          self.dname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 2:
        if ftype == TType.STRING:
          self.bdname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 3:
        if ftype == TType.STRING:
          self.ip = iprot.readString();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('add_backet_ip_args')
    if self.dname is not None:
      oprot.writeFieldBegin('dname', TType.STRING, 1)
      oprot.writeString(self.dname)
      oprot.writeFieldEnd()
    if self.bdname is not None:
      oprot.writeFieldBegin('bdname', TType.STRING, 2)
      oprot.writeString(self.bdname)
      oprot.writeFieldEnd()
    if self.ip is not None:
      oprot.writeFieldBegin('ip', TType.STRING, 3)
      oprot.writeString(self.ip)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

class add_backet_ip_result(object):
  """
  Attributes:
   - success
  """

  thrift_spec = (
    (0, TType.BOOL, 'success', None, None, ), # 0
  )

  def __init__(self, success=None,):
    self.success = success

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 0:
        if ftype == TType.BOOL:
          self.success = iprot.readBool();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('add_backet_ip_result')
    if self.success is not None:
      oprot.writeFieldBegin('success', TType.BOOL, 0)
      oprot.writeBool(self.success)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

class rmv_backet_ip_args(object):
  """
  Attributes:
   - dname
   - bdname
   - ip
  """

  thrift_spec = (
    None, # 0
    (1, TType.STRING, 'dname', None, None, ), # 1
    (2, TType.STRING, 'bdname', None, None, ), # 2
    (3, TType.STRING, 'ip', None, None, ), # 3
  )

  def __init__(self, dname=None, bdname=None, ip=None,):
    self.dname = dname
    self.bdname = bdname
    self.ip = ip

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 1:
        if ftype == TType.STRING:
          self.dname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 2:
        if ftype == TType.STRING:
          self.bdname = iprot.readString();
        else:
          iprot.skip(ftype)
      elif fid == 3:
        if ftype == TType.STRING:
          self.ip = iprot.readString();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('rmv_backet_ip_args')
    if self.dname is not None:
      oprot.writeFieldBegin('dname', TType.STRING, 1)
      oprot.writeString(self.dname)
      oprot.writeFieldEnd()
    if self.bdname is not None:
      oprot.writeFieldBegin('bdname', TType.STRING, 2)
      oprot.writeString(self.bdname)
      oprot.writeFieldEnd()
    if self.ip is not None:
      oprot.writeFieldBegin('ip', TType.STRING, 3)
      oprot.writeString(self.ip)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

class rmv_backet_ip_result(object):
  """
  Attributes:
   - success
  """

  thrift_spec = (
    (0, TType.BOOL, 'success', None, None, ), # 0
  )

  def __init__(self, success=None,):
    self.success = success

  def read(self, iprot):
    if iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, (self.__class__, self.thrift_spec))
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 0:
        if ftype == TType.BOOL:
          self.success = iprot.readBool();
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, (self.__class__, self.thrift_spec)))
      return
    oprot.writeStructBegin('rmv_backet_ip_result')
    if self.success is not None:
      oprot.writeFieldBegin('success', TType.BOOL, 0)
      oprot.writeBool(self.success)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def validate(self):
    return


  def __repr__(self):
    L = ['%s=%r' % (key, value)
      for key, value in self.__dict__.iteritems()]
    return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)
