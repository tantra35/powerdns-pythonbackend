from playrix.powerDNS import QType;
import logging;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class backend:
  def __init__(self, qname, options):
    self.__m_lookup_responce_iter = None;
    self.__m_qname = qname;
    self.__m_loger = logging.getLogger("playrix.powerDNS.g300_net"); 

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    l_qtypeCode = qtype.getCode();
    l_lookup_responce = [];
    self.__m_lookup_iter = None;
    l_lqdomain = qdomain.lower();

    if l_lqdomain == "g300.net":
      if l_qtypeCode == QType.NS or l_qtypeCode == QType.ANY:
        l_lookup_responce.append({'type': QType.NS, 'data': 'ns1.g300.net', 'qname': qdomain, 'domain_id': 10});
        l_lookup_responce.append({'type': QType.NS, 'data': 'ns2.g300.net', 'qname': qdomain, 'domain_id': 10});

    elif l_lqdomain == "ns1.g300.net":
      if l_qtypeCode == QType.ANY or l_qtypeCode == QType.A:
        l_lookup_responce.append({'type': QType.A, 'data': "176.9.15.229", 'qname': qdomain, 'domain_id': 10});

    elif l_lqdomain == "ns2.g300.net":
      if l_qtypeCode == QType.ANY or l_qtypeCode == QType.A:
        l_lookup_responce.append({'type': QType.A, 'data': "77.88.21.3", 'qname': qdomain, 'domain_id': 10});

    if len(l_lookup_responce):
      self.__m_lookup_responce_iter = iter(l_lookup_responce);


  def list(self, qdomain, domain_id):
    self.__m_loger.debug("call with qdomain: " + qdomain);
    self.__m_loger.debug("call with domain_id: " + str(domain_id));

    l_lqdomain = qdomain.lower();
    self.__m_lookup_iter = None;
    retval = False;

    if l_lqdomain == "g300.net":
      l_lookup_responce = [];
      retval = True;

      l_lookup_responce.append({'type': QType.NS, 'data': 'ns1.g300.net', 'qname': qdomain, 'domain_id': domain_id});
      l_lookup_responce.append({'type': QType.NS, 'data': 'ns2.g300.net', 'qname': qdomain, 'domain_id': domain_id});

      l_lookup_responce.append({'type': QType.A, 'data': "176.9.15.229", 'qname': qdomain, 'domain_id': domain_id});
      l_lookup_responce.append({'type': QType.A, 'data': "77.88.21.3", 'qname': qdomain, 'domain_id': domain_id});

      self.__m_lookup_responce_iter = iter(l_lookup_responce);

    return retval;

  def get(self, dnsresrecord):
    self.__m_loger.debug("call");
    retval = False;

    if self.__m_lookup_responce_iter:
      l_item = next(self.__m_lookup_responce_iter, False);

      if l_item:
        dnsresrecord.qtype = QType(l_item['type']);
        dnsresrecord.ttl = 60;
        dnsresrecord.priority = 0;
        dnsresrecord.last_modified = 0;
        dnsresrecord.qname = l_item['qname'];
        dnsresrecord.content = l_item['data'];
        dnsresrecord.domain_id = l_item['domain_id'];

        retval = True;

    return retval;

  def getSOA(self, name, soadata, dnspkt):
    self.__m_loger.debug("call with name " + name);
    self.__m_loger.debug("call from remote addr " + ("Request made by powerDNS himself" if dnspkt is None else dnspkt.getRemote()));

    if name == "g300.net":
      soadata.qname = "g300.net";
      soadata.nameserver = "ns1.g300.net";
      soadata.hostmaster = "support.playrix.com";
      soadata.ttl = 86400;
      soadata.default_ttl = 3600;

      soadata.refresh = 3600;
      soadata.retry = 2*soadata.refresh;
      soadata.expire = 7*soadata.refresh;

      soadata.serial = 610;
      soadata.domain_id = 10;

      return True;

    return False;
