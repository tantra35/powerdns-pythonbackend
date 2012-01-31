#!/usr/bin/python

import GeoIP;
import math;

def distance(point1, point2):
  retval = -1;

  try:
    l_longitude = math.pow(point1['longitude'] - point2['longitude'], 2);
    l_latitude = math.pow(point1['latitude'] - point2['latitude'], 2);

    retval = math.sqrt(l_longitude + l_latitude);

  except:
    pass;

  return retval;


gi = GeoIP.open("/usr/share/GeoIP/GeoIPCity.dat", GeoIP.GEOIP_MEMORY_CACHE);
#gi = GeoIP.open("/usr/share/GeoIP/GeoIP.dat", GeoIP.GEOIP_MEMORY_CACHE);

ips = ('188.27.155.221', '188.134.33.152', '108.59.160.189', '92.54.194.79', '178.45.19.175', '81.163.176.44', '85.141.100.115', '164.127.240.24', '69.171.228.249', '66.220.158.251', '94.232.177.12', '75.130.92.205');
amsterdamcoords={'longitude':4.89, 'latitude': 52.37};

for ip in ips:
    l_ip1record = gi.record_by_addr(ip);
    l_distance = distance(amsterdamcoords, l_ip1record);

    print "for ip: %s" % (ip);
    print l_distance
    print "", ""
