from playrix.powerDNS import QType;
import logging;

import GeoIP;
import math;

from playrix.powerDNS.BackendComunicate import *;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class backend:
  def __init__(self, qname, options):
    self.__m_geo = GeoIP.open(options[0], GeoIP.GEOIP_STANDARD);
    self.__m_qname = qname;
    self.__m_loger = logging.getLogger("playrix.powerDNS.geowithloadbalancewithfailover");

  @staticmethod
  def __distance(point1, point2):
    retval = -1;

    try:
      l_longitude = math.pow(point1['longitude'] - point2['longitude'], 2);
      l_latitude = math.pow(point1['latitude'] - point2['latitude'], 2);

      retval = math.sqrt(l_longitude + l_latitude);

    except:
      pass;

    return retval;

  def __getdata(self):
    with g_rlock.readlock:
      retval = g_root;
      self.__m_loger.debug(retval);

    return retval;


  def list(self, qtype, qdomain, dnspkt, domain_id):
    l_domains = self.__getdata();

    l_qtypeCode = qtype.getCode();
    l_lookup_responce = [];
    l_lqdomain = qdomain.lower();

    if l_lqdomain in l_domains:
      if l_qtypeCode == QType.ANY or l_qtypeCode == QType.A:
        l_domain = l_domains[l_lqdomain];
        l_backets = l_domain['backets'];

        l_distance = 0xffffffff;
        l_nearest_backet = None;
        l_default_backet = None;
        l_withip_backet = None;

        l_ip_record = self.__m_geo.record_by_addr(dnspkt.getRemote());
        l_ip_point = l_ip_record;

        for l_bname, l_bvalue in l_backets.iteritems():
          ll_distance = self.__distance(l_bvalue, l_ip_point);

          if (0 < ll_distance) and (ll_distance < l_distance) and len(l_bvalue['ips']):
            l_distance = ll_distance;
            l_nearest_backet = l_bvalue;

          if not l_default_backet and len(l_bvalue['ips']) and ('default' in l_bvalue and l_bvalue['default']):
            l_default_backet = l_bvalue;

          if l_withip_backet is None and len(l_bvalue['ips']):
            l_withip_backet = l_bvalue;

        else:
          if l_default_backet is None:
            l_default_backet = l_withip_backet;

          if l_nearest_backet is None:
            l_nearest_backet = l_default_backet;

        if l_nearest_backet:
          self.__m_loger.info("for client ip " + dnspkt.getRemote() + " find backet " + l_nearest_backet["name"]);

          for l_ip in l_nearest_backet['ips']:
            l_lookup_responce.append({'type': QType.A, 'content': l_ip, 'qname': qdomain, 'ttl': l_domain['ttl']});

        else:
          self.__m_loger.warning("can't find any backet for client ip " + dnspkt.getRemote());

    return l_lookup_responce;
