import ConfigParser;
import logging;
import logging.handlers;
import traceback;
import re;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
def removeComments(string):
  return re.sub(re.compile("(#|;).*$", re.MULTILINE) ,"" ,string) # remove all occurance singleline comments (//COMMENT\n ) from string

def cmpdomains(d1, d2):
  l_d1 = d1.split('.')
  l_d2 = d2.split('.')

  if(len(l_d1) > len(l_d2)):
    return 1

  elif(len(l_d1) < len(l_d2)):
    return -1

  else:
    return cmp(d1, d2)

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class loader(object):
  def __init__(self):
    self.__m_domain_to_class = {};
    self.__m_handler = None;
    self.__m_loger = logging.getLogger("loader");

    try:
      l_config = g_config;

      for l_domainname in l_config.sections():
        l_module_name, l_class_name  = l_config.get(l_domainname, 'class').rsplit('.', 1);
        l_zone_id = int(l_config.get(l_domainname, 'zone_id'));
        l_options = [];

        l_module =__import__(l_module_name, globals(), locals(), ['']);
        l_class = getattr(l_module, l_class_name);

        for l_option in l_config.items(l_domainname):
          l_name, l_value = l_option;
          l_value = removeComments(l_value)
          l_rrnames = ('a', 'ns', 'cname', 'soa', 'txt')

          if l_name in l_rrnames:
            if l_name == 'soa':
              lll_option = [];

              for l_line in str.splitlines(l_value):
                if l_line != '':
                  lll_option.append(l_line);

              ll_option = (l_name, ' '.join(lll_option))
              l_options.append(ll_option);

            else:
              for l_line in str.splitlines(l_value):
                if l_line != '':
                  ll_option = (l_name, l_line);
                  l_options.append(ll_option);

        l_ldomainname = l_domainname.lower();
        self.__m_domain_to_class[l_ldomainname] = l_class(l_ldomainname, l_zone_id, l_options);

      self.__m_domains = self.__m_domain_to_class.keys();
      self.__m_domains.sort(cmp=cmpdomains, reverse=True);

    except Exception as e:
      self.__m_loger.error(traceback.format_exc());
      raise e

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    self.__m_loger.debug("call with qtype: " + str(qtype));
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with dnspkt: " + str(dnspkt));
    self.__m_loger.debug("call with domain_id: " + str(domain_id));

    self.__m_handler = None;
    l_lqdomain = qdomain.lower();

    for l_qdomain in self.__m_domains:
      ll_qdomain = '.' + l_qdomain;

      if (l_lqdomain == l_qdomain) or (l_lqdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        l_handler = self.__m_domain_to_class[l_qdomain]

        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        l_handler.lookup(qtype, l_lqdomain, dnspkt, domain_id);

        break;

  def list(self, qdomain, domain_id):
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with domain_id: " + str(domain_id));

    self.__m_handler = None;
    retval = False;
    l_lqdomain = qdomain.lower();

    for l_qdomain in self.__m_domains:
      ll_qdomain = '.' + l_qdomain;

      if (l_lqdomain == l_qdomain) or (l_lqdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        l_handler = self.__m_domain_to_class[l_qdomain]

        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        retval = l_handler.list(l_lqdomain, domain_id);

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
    l_lqdomain = qdomain.lower();

    for l_qdomain in self.__m_domains:
      ll_qdomain = '.' + l_qdomain;

      if (l_lqdomain == l_qdomain) or (l_lqdomain.find(ll_qdomain, -len(ll_qdomain)) > 0):
        l_handler = self.__m_domain_to_class[l_qdomain]

        self.__m_loger.debug("call with handler: " + str(l_handler));
        self.__m_handler = l_handler;
        retval = l_handler.getSOA(l_lqdomain, soadata, dnspkt);

        break;

    return retval;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
__LEVELS = {'debug': logging.DEBUG,
          'info': logging.INFO,
          'warning': logging.WARNING,
          'error': logging.ERROR,
          'critical': logging.CRITICAL}

g_config = ConfigParser.SafeConfigParser()
g_config.read('/etc/powerdns/loader.cfg');

try:
  __logfile = g_config.get('global', 'logfile')
  __level = __LEVELS[g_config.get('global', 'loglevel')]

  __root_logger_handler = logging.handlers.TimedRotatingFileHandler(__logfile, when='d', backupCount=7);
  __root_logger_handler.suffix = "%Y-%m-%d";
  __root_logger_handler.setFormatter(logging.Formatter("%(asctime)s %(levelname)s %(name)s::%(funcName)s  %(message)s"));

  __root_logger = logging.getLogger('');
  __root_logger.addHandler(__root_logger_handler);
  __root_logger.setLevel(__level);

except Exception as e:
  pass;

finally:
  g_config.remove_section('global');
