#!/usr/bin/python

root = {};

def add_backet(dname, bdname, longitude, latitude, ttl, default=False):
  if not dname in root:
    root[dname] = {};

  root[dname][bdname] = {'longitude': longitude, 'latitude': latitude, 'ips': [], 'ttl': ttl};

  if default:
    root[dname][bdname]['default'] = True;

def add_backet_ip(dname, bdname, ip):
  if not ip in root[dname][bdname]['ips']:
    root[dname][bdname]['ips'].append(ip);
