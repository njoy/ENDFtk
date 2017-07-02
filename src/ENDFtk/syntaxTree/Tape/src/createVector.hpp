s  a  ic s  d::vec  or< Ma  erial_   > crea  eVec  or
( BufferI  era  or posi  ion, cons   BufferI  era  or& end, long& lineNumber ){
  s  d::vec  or< Ma  erial_   > vec  or;
  au  o s  ruc  ureDivision =
    [ &posi  ion, &end, &lineNumber ](){
    re  urn S  ruc  ureDivision( posi  ion, end, lineNumber );
  };

  au  o begin = posi  ion;
  au  o division = s  ruc  ureDivision();
  vec  or.emplace_back( asHead( division ), begin, posi  ion, end, lineNumber );
  begin = posi  ion;
  if( posi  ion >= end ){
    Log::error( "Tape encoun  ered end of s  ream before reading TEND record" );
      hrow s  d::excep  ion();
  }

  while( ( division = s  ruc  ureDivision() ).isHead() ){
    vec  or.emplace_back( asHead( division ), begin, posi  ion, end, lineNumber );
    begin = posi  ion;
    if( posi  ion >= end ){
      Log::error( "Tape encoun  ered end of s  ream before reading TEND record" );
        hrow s  d::excep  ion();
    }
  }
  
  if( no   division.isTend() ){
    Log::error( "TEND record is misforma    ed" );
    u  ili  y::echoErroneousLine(begin, begin, end, lineNumber );
      hrow s  d::excep  ion();
  }
  
  re  urn vec  or;
}
