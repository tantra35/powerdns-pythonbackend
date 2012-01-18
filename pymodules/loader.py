import ConfigParser;
import logging;
import re;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class loader(object):
  def __init__(self):
    self.__m_domain_to_class = {};
    self.__m_wildcarddomain_to_class = {};
    self.__m_handler = None;
    self.__m_loger = logging.getLogger("loader");

    l_config = ConfigParser.ConfigParser()
    l_config.read('/etc/powerdns/loader.cfg');

    for l_domainname in l_config.sections():
      l_module_name = l_config.get(l_domainname, 'module');
      l_class_name = l_config.get(l_domainname, 'class');

      l_module =__import__(l_module_name, globals(), locals(), ['']);
      l_class = getattr(l_module, l_class_name);

      if l_domainname[0] == "~":
        l_wildcarddomain = ".*" + re.sub(r"\.", "\\.", l_domainname[1:]) + "$";
        self.__m_wildcarddomain_to_class[l_wildcarddomain] = l_class(l_domainname, l_config.items(l_domainname));

      else:
        self.__m_domain_to_class[l_domainname] = l_class(l_domainname, l_config.items(l_domainname));

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    self.__m_handler = None;

    if qdomain in self.__m_domain_to_class:
      l_handler = self.__m_domain_to_class[qdomain];
      self.__m_handler = l_handler;
      l_handler.lookup(qtype, qdomain, dnspkt, domain_id);

    else:
      for l_wildcarddomain, l_handler in self.__m_wildcarddomain_to_class.iteritems():
        if re.match(l_wildcarddomain, qdomain):
          self.__m_handler = l_handler;
          l_handler.lookup(qtype, qdomain, dnspkt, domain_id);

          break;

  def list(self, qdomain, domain_id):
    self.__m_handler = None;
    retval = False;

    if qdomain in self.__m_domain_to_class:
      l_handler = self.__m_domain_to_class[qdomain];
      self.__m_handler = l_handler;
      retval = l_handler.list(qdomain, domain_id);

    else:
      for l_wildcarddomain, l_handler in self.__m_wildcarddomain_to_class.iteritems():
        if re.match(l_wildcarddomain, qdomain):
          self.__m_handler = l_handler;
          retval = l_handler.list(qdomain, domain_id);

          break;

    return retval;

  def get(self, dnsresrecord):
    if self.__m_handler:
      return self.__m_handler.get(dnsresrecord)

    return False;

  def getSOA(self, qdomain, soadata, dnspkt):
    self.__m_handler = None;
    retval = False;

    if qdomain in self.__m_domain_to_class:
      l_handler = self.__m_domain_to_class[qdomain];
      self.__m_handler = l_handler;
      retval = l_handler.getSOA(qdomain, soadata, dnspkt);

    else:
      for l_wildcarddomain, l_handler in self.__m_wildcarddomain_to_class.iteritems():
        self.__m_loger.debug(l_wildcarddomain);

        if re.match(l_wildcarddomain, qdomain):
          self.__m_handler = l_handler;
          retval = l_handler.getSOA(qdomain, soadata, dnspkt);

          break;

    return retval;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
logging.basicConfig(filename="/var/log/powerdns/python.test.log", level=logging.DEBUG, format="%(asctime)s - %(name)s - %(levelname)s  - %(funcName)s  - %(message)s");
