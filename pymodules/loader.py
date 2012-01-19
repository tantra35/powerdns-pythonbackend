import ConfigParser;
import logging;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class loader(object):
  def __init__(self, confpath = '/etc/powerdns/loader.cfg'):
    self.__m_domain_to_class = {};
    self.__m_handler = None;
    self.__m_loger = logging.getLogger("loader");

    l_config = ConfigParser.SafeConfigParser()
    l_config.read(confpath);

    for l_domainname in l_config.sections():
      l_module_name, l_class_name  = l_config.get(l_domainname, 'class').rsplit('.', 1);
      l_zone_id = int(l_config.get(l_domainname, 'zone_id'));
      l_options = [];

      l_module =__import__(l_module_name, globals(), locals(), ['']);
      l_class = getattr(l_module, l_class_name);

      for l_option in l_config.items(l_domainname):
        l_name, l_value = l_option;
        l_rrnames = ('a', 'ns', 'cname', 'soa', 'txt')

        if l_name in l_rrnames:
          for l_line in str.splitlines(l_value):
            if l_line != '':
              ll_option = (l_name, l_line);
              l_options.append(ll_option);

      self.__m_domain_to_class[l_domainname] = l_class(l_domainname, l_zone_id, l_options);

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    self.__m_loger.debug("call with qtype: " + str(qtype));
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with dnspkt: " + str(dnspkt));
    self.__m_loger.debug("call with domain_id: " + str(domain_id));

    self.__m_handler = None;

    for l_qdomain, l_handler in self.__m_domain_to_class.iteritems():
      ll_qdomain = '.' + l_qdomain;

      if (qdomain == l_qdomain) or (qdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        l_handler.lookup(qtype, qdomain, dnspkt, domain_id);

        break;

  def list(self, qdomain, domain_id):
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with domain_id: " + str(domain_id));

    self.__m_handler = None;
    retval = False;

    for l_qdomain, l_handler in self.__m_domain_to_class.iteritems():
      ll_qdomain = '.' + l_qdomain;

      if (qdomain == l_qdomain) or (qdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        retval = l_handler.list(qdomain, domain_id);

        break;

    return retval;

  def get(self, dnsresrecord):
    if self.__m_handler:
      self.__m_loger.debug("call with handler: " + str(self.__m_handler));
      return self.__m_handler.get(dnsresrecord)

    return False;

  def getSOA(self, qdomain, soadata, dnspkt):
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with dnspkt: " + str(dnspkt));

    self.__m_handler = None;
    retval = False;

    for l_qdomain, l_handler in self.__m_domain_to_class.iteritems():
      ll_qdomain = '.' + l_qdomain;

      if (qdomain == l_qdomain) or (qdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        retval = l_handler.getSOA(qdomain, soadata, dnspkt);

        break;

    return retval;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
logging.basicConfig(filename="/var/log/powerdns/python.test.log", level=logging.DEBUG, format="%(asctime)s %(levelname)s %(name)s::%(funcName)s  %(message)s");
