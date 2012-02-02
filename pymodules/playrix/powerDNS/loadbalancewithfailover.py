from playrix.powerDNS import QType;
import logging;

from playrix.powerDNS.BackendComunicate import *;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class backend:
  def __init__(self, qname, options):
    self.__m_qname = qname;
    self.__m_loger = logging.getLogger("playrix.powerDNS.loadbalancewithfailover");

  def __getdata(self):
    with g_rlock.readlock:
      retval = g_root;
      self.__m_loger.debug(retval);

    return retval;

  def list(self, qtype, qdomain, dnspkt, domain_id):
    l_domains = self.__getdata();

    l_qtypeCode = qtype.getCode();
    l_lookup_responce = [];

    if qdomain in l_domains:
      l_domain = l_domains[qdomain];
      l_backets = l_domain['backets'];

      if 'LB' in l_backets:
        l_backet = l_backets['LB'];

        for l_ip in l_backet['ips']:
          l_lookup_responce.append({'type': QType.A, 'content': l_ip, 'qname': qdomain, 'ttl': l_domain['ttl']});

      else:
        self.__m_loger.warning("no LB backet");

    return l_lookup_responce;
