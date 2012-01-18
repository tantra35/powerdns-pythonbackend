from playrix.powerDNS import QType;
import logging;

import GeoIP;
import math;

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
class test(object):
  def __init__(self):
#    self.__m_geo = GeoIP.open("/usr/share/GeoIP/GeoIPCity.dat", GeoIP.GEOIP_MEMORY_CACHE);
    self.__m_geo = GeoIP.open("/usr/share/GeoIP/GeoIPCity.dat", GeoIP.GEOIP_STANDARD);
    self.__m_lookup_responce_iter = None;

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

  def lookup(self, qtype, qdomain, dnspkt, domain_id):
    logging.debug("call from remote addr: " + dnspkt.getRemote());
    logging.debug("call with qtype: " + str(qtype));
    logging.debug("call with qdomain: " + qdomain);
    logging.debug("call with domain_id: " + str(domain_id));

    l_domain_backets = {
      'g21.g300.net': {
        'USA': {'longitude': -73, 'latitude': 40, 'ips': ['1.1.1.1', '209.222.8.131']},
        'EUR': {'longitude': 4, 'latitude': 52, 'ips': ['146.185.23.162', '82.192.95.147', '85.17.31.103']}
      },

      'g22.g300.net':
      {
        'USA': {'longitude': -73, 'latitude': 40, 'ips': ['1.1.1.1', '209.222.8.131']}
      }
    }

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

    elif l_lqdomain in l_domain_backets:
      if l_qtypeCode == QType.ANY or l_qtypeCode == QType.A:
        l_distance = 0xffffffff;
        l_nearest_backet = None;

        l_ip_record = self.__m_geo.record_by_addr(dnspkt.getRemote());
        l_ip_point = l_ip_record;
        l_backets = l_domain_backets[l_lqdomain];

        for l_bname, l_bvalue in l_backets.iteritems():
          l_backet_point = {'longitude': l_bvalue['longitude'], 'latitude': l_bvalue['latitude']};
          ll_distance = self.__distance(l_backet_point, l_ip_point);

          if (0 < ll_distance) and (ll_distance < l_distance):
            l_distance = ll_distance;
            l_nearest_backet = l_bvalue;

        else:
          if not l_nearest_backet:
            l_nearest_backet = l_bvalue;

        for l_ip in l_nearest_backet['ips']:
          l_lookup_responce.append({'type': QType.A, 'data': l_ip, 'qname': qdomain, 'domain_id': 10});

    if len(l_lookup_responce):
      self.__m_lookup_responce_iter = iter(l_lookup_responce);


  def list(self, target, domain_id):
    logging.debug("call with target: " + target);

    return False;

  def get(self, dnsresrecord):
    logging.debug("call");
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
    logging.debug("call with name " + name);
    logging.debug("call from remote addr " + dnspkt.getRemote());

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

#------------------------------------------------------------------------------
#
#
#
#------------------------------------------------------------------------------
logging.basicConfig(filename="/var/log/powerdns/python.test.log", level=logging.DEBUG, format="%(asctime)s - %(levelname)s  - %(funcName)s  - %(message)s");
