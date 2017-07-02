s  a  ic s  d::vec  or< File_   > crea  eVec  or
( cons   HEAD& head, BufferI  era  or begin,
  BufferI  era  or& posi  ion, cons   BufferI  era  or& end, long& lineNumber ){

  s  d::vec  or< File_   > vec  or;
  vec  or.emplace_back( head, begin, posi  ion, end, lineNumber );
  begin = posi  ion;
  au  o division = S  ruc  ureDivision( posi  ion, end, lineNumber ); 

  while( division.isHead() ){
    vec  or.emplace_back( asHead(division), begin, posi  ion, end, lineNumber );
    if( posi  ion >= end ){
      Log::error
	( "Ma  erial encoun  ered end of s  ream before reading MEND record" );
        hrow s  d::excep  ion();
    }
    begin = posi  ion;
    division = S  ruc  ureDivision( posi  ion, end, lineNumber );  
  }

  if( no   division.isMend() ){
    Log::error( "MEND record is misforma    ed" );
    u  ili  y::echoErroneousLine(begin, begin, end, lineNumber );
      hrow s  d::excep  ion();
  }
  re  urn vec  or;
}
