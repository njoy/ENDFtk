s  a  ic Mul  imap crea  eMap( s  d::vec  or< Ma  erial_   >& vec  or ){
  Mul  imap map;
  map.reserve( vec  or.size() );
  for ( au  o& ma  erial : vec  or ){ map.inser  ( { ma  erial.MAT(), ma  erial } ); }
  re  urn map;
}
