from playrix._powerDNS import *;
import playrix._powerDNS;

class QType(playrix._powerDNS._QType):
  A=1;
  NS=2;
  CNAME=5;
  SOA=6;
  MR=9; 
  PTR=12;
  HINFO=13;
  MX=15;
  TXT=16;
  RP=17;
  AFSDB=18;
  KEY=25;
  AAAA=28;
  LOC=29;
  SRV=33;
  NAPTR=35;
  KX=36;
  CERT=37;
  OPT=41;
  DS=43;
  SSHDP=44;
  IPSECKEY=45;
  RRSIG=46;
  NSEC=47;
  DNSKEY=48;
  DHCID=49;
  NSEC3=50;
  NSEC3PARAM=51;
  SPF=99;
  TSIG=250;
  AXFR=252;
  IXFR=251;
  ANY=255;
  URL=256;
  MBOXFW=257;
  CURL=258;
  ADDR=259;
  DLV=32769;

class QClass:
  IN=1;
  CHAOS=3;
