def test():
  l_backets = {
    'USA': {'longitude': -73, 'latitude': 40, 'ips': ['1.1.1.1', '209.222.8.131']},
    'EUR': {'longitude': 4, 'latitude': 52, 'ips': ['146.185.23.162', '82.192.95.147', '85.17.31.103']}
  }

  for l_bname, l_bvalue in l_backets.iteritems():
    print l_bname;

  else:
    print "the end :-))";
    print l_bname;


#test();
import re;
import ConfigParser; 

l_domainname = "~g300.net";
l_wildcarddomain = ".*" + re.sub(r"\.", "\\.", l_domainname[1:]) + "$";

print re.match(l_wildcarddomain, ".g300.net");


l_config = ConfigParser.ConfigParser();
l_config.read('example.cfg'); 

print l_config.items("~g300.net");