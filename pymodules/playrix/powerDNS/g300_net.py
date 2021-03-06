from playrix.powerDNS import QType;
import logging;
import re;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class backend:
  def __init__(self, qname, zone_id, options):
    self.__m_lookup_responce_iter = None;
    self.__m_qdomains = {};
    self.__m_loger = logging.getLogger("playrix.powerDNS.g300_net");
    self.__m_zone_id = zone_id
    self.__m_qname = qname;

    for l_option in options:
      l_name, l_value = l_option;

      if l_name == 'a':
        l_parts = l_value.split();

        if l_parts[0] == '@':
          l_lqdomain = qname

        else:
          l_lqdomain = (l_parts[0] if '.' in l_parts[0] else l_parts[0] + '.' + qname).lower();

        if not l_lqdomain in self.__m_qdomains:
          self.__m_qdomains[l_lqdomain] = {};

        if not 'A' in self.__m_qdomains[l_lqdomain]:
          self.__m_qdomains[l_lqdomain]['A'] = [];

        if re.match('\d+\.\d+\.\d+\.\d+', l_parts[1]):
          self.__m_qdomains[l_lqdomain]['A'].append({'type': QType.A, 'content': l_parts[1], 'qname': l_lqdomain, 'ttl': int(l_parts[2])})

        elif l_parts[1].find('class:') == 0:
          l_module_name, l_class_name = l_parts[1][6:].rsplit('.', 1);

          l_module =__import__(l_module_name, globals(), locals(), ['']);
          l_class = getattr(l_module, l_class_name);

          self.__m_qdomains[l_lqdomain]['A'].append({'handler': l_class(qname, l_parts[2:])});

      elif l_name == 'ns':  
        l_parts = l_value.split();

        if l_parts[0] == '@':
          l_lqdomain = qname

        else:
          l_lqdomain = (l_parts[0] if '.' in l_parts[0] else l_parts[0] + '.' + qname).lower();

        if not l_lqdomain in self.__m_qdomains:
          self.__m_qdomains[l_lqdomain] = {};

        if not 'NS' in self.__m_qdomains[l_lqdomain]:
          self.__m_qdomains[l_lqdomain]['NS'] = [];

        l_rr = {'type': QType.NS, 'content': l_parts[1], 'qname': l_lqdomain, 'ttl': int(l_parts[2])}
        self.__m_qdomains[l_lqdomain]['NS'].append(l_rr);

      elif l_name == 'cname':
        pass;

      elif l_name == "soa":
        l_parts = l_value.split();
        l_lqdomain = qname;

        if not l_lqdomain in self.__m_qdomains:
          self.__m_qdomains[l_lqdomain] = {};

        l_rr = {
          'nameserver': l_parts[0],
          'hostmaster': l_parts[1].replace('@', '.'),
          'ttl': int(l_parts[2]), 
          'serial': int(l_parts[3]), 
          'refresh': int(l_parts[4]),
          'retry': int(l_parts[5]),
          'expire': int(l_parts[6]),
          'default_ttl': int(l_parts[7])
        }

        self.__m_qdomains[l_lqdomain]['SOA'] = l_rr;

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    l_qtypeCode = qtype.getCode();
    l_lookup_responce = [];
    self.__m_lookup_iter = None;

    if qdomain in self.__m_qdomains:
      self.__m_loger.debug("request results for domain: " + qdomain)
      l_qdomaindata = self.__m_qdomains[qdomain];

      if l_qtypeCode == QType.NS or l_qtypeCode == QType.ANY:
        if 'NS' in l_qdomaindata:
          for l_rrecord in l_qdomaindata['NS']:
            l_lookup_responce.append(l_rrecord);

      if l_qtypeCode == QType.ANY or l_qtypeCode == QType.A:
        if 'A' in l_qdomaindata:
          for l_rrecord in l_qdomaindata['A']:
            if 'handler' in l_rrecord:
              for ll_rrecord in l_rrecord['handler'].list(qtype, qdomain, dnspkt, domain_id):
                l_lookup_responce.append(ll_rrecord);

            else:
              l_lookup_responce.append(l_rrecord);

    self.__m_loger.debug(l_lookup_responce)

    if len(l_lookup_responce):
      self.__m_lookup_responce_iter = iter(l_lookup_responce);


  def list(self, qdomain, domain_id):
    l_lookup_responce = [];
    self.__m_lookup_responce_iter = None;
    retval = False;

    for l_qdomain, l_qdomaindata in self.__m_qdomains.iteritems():
      for l_rrname, ll_qdomaindata in l_qdomaindata.iteritems():
        if l_rrname != 'SOA':
          for l_rrecord in ll_qdomaindata:
            if not 'handler' in l_rrecord:
              l_lookup_responce.append(l_rrecord);

    self.__m_loger.debug(l_lookup_responce);

    if len(l_lookup_responce):
      self.__m_lookup_responce_iter = iter(l_lookup_responce);
      retval = True;

    return retval;

  def get(self, dnsresrecord):
    retval = False;

    if self.__m_lookup_responce_iter:
      l_item = next(self.__m_lookup_responce_iter, False);
      self.__m_loger.debug(l_item)

      if l_item:
        dnsresrecord.qtype = QType(l_item['type']);
        dnsresrecord.ttl = l_item['ttl'];
        dnsresrecord.priority = 0;
        dnsresrecord.last_modified = 0;
        dnsresrecord.qname = l_item['qname'];
        dnsresrecord.content = l_item['content'];
        dnsresrecord.domain_id = self.__m_zone_id;

        retval = True;

    return retval;

  def getSOA(self, qdomain, soadata, dnspkt):
    if qdomain == self.__m_qname:
      l_rr = self.__m_qdomains[qdomain]['SOA'];

      soadata.qname = qdomain;
      soadata.nameserver = l_rr['nameserver'];
      soadata.hostmaster = l_rr['hostmaster'];
      soadata.serial = l_rr['serial'];
      soadata.refresh = l_rr['refresh'];

      soadata.ttl = l_rr['ttl'];
      soadata.default_ttl = l_rr['default_ttl'];

      soadata.retry = l_rr['retry'];
      soadata.expire = l_rr['expire'];

      soadata.domain_id = self.__m_zone_id;

      return True;

    return False;
