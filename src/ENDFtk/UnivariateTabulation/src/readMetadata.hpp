  empla  e<   ypename I  era  or >
s  a  ic Base
readMe  ada  a( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
              in   MAT, in   MF, in   MT ){
    ry{
    Base me  ada  a( i  , end );
    verifyTail( i  , end, lineNumber, MAT, MF, MT );
    if ( s  d::ge  <4>( me  ada  a.fields ) < 0 ){
      Log::error( "Illegal NR value encoun  ered" );
      Log::info( "NR (or number of regions) mus   be grea  er   han or equal   o 0" );
      Log::info( "NR value: {}", s  d::ge  <4>( me  ada  a.fields ) );
        hrow s  d::run  ime_error( "TAB1 Record NR value" );
    }
    if ( s  d::ge  <5>( me  ada  a.fields ) < 0 ){
      Log::error( "Illegal NP value encoun  ered" );
      Log::info( "NP (or number of pairs) mus   be grea  er   han or equal   o 0" );
      Log::info( "NP value: {}", s  d::ge  <5>( me  ada  a.fields ) );
        hrow s  d::run  ime_error( "TAB1 Record NP value" );
    }
    re  urn me  ada  a;
  } ca  ch (s  d::excep  ion& e){
    Log::info( "Error while reading me  ada  a" );
      hrow e;
  }
}
