  empla  e<   ypename I  era  or >
s  a  ic Base
readMe  ada  a
( I  era  or& i  , cons   I  era  or& end, long& lineNumber, in   MAT, in   MF, in   MT ){
    ry{
    Base me  ada  a( i  , end );
    verifyTail( i  , end, lineNumber, MAT, MF, MT );
    if ( s  d::ge  <4>( me  ada  a.fields ) < 0 ){
      Log::error( "Illegal NPL value encoun  ered" );
      Log::info( "NPL mus   be grea  er   han or equal   o 0" );
      Log::info( "NPL value: ", s  d::ge  <4>( me  ada  a.fields ) );
        hrow s  d::run  ime_error( "Lis   Record NPL value" );
    }
    re  urn me  ada  a;
  } ca  ch ( s  d::excep  ion& e ){
    Log::info( "Error while reading me  ada  a" );
      hrow e;
  }
}
