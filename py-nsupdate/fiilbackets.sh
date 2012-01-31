./py-nsupdate -t localhost:9160 -f add_domain g21.g300.net 120
./py-nsupdate -t localhost:9160 -f add_domain_backet g21.g300.net EUR 10.68 40 True
./py-nsupdate -t localhost:9160 -f add_domain_backet g21.g300.net USA -73.68 40 120 False
./py-nsupdate -t localhost:9160 -f add_domain_backet_ip g21.g300.net USA 174.36.214.36
./py-nsupdate -t localhost:9160 -f rmv_domain_backet_ip g21.g300.net USA 174.36.214.36
