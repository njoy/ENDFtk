  empla  e<   ypename I  era  or >
s  a  ic void readSEND
( I  era  or& i  , cons   I  era  or& end, long& lineNumber, in   MAT, in   MF ){
    ry{
    cons   au  o begin = i  ;
    au  o division = S  ruc  ureDivision( i  , end, lineNumber );
    if( no   division.isSend() ){
      Log::error( "Malforma    ed SEND record." );
      u  ili  y::echoErroneousLine( begin, i  , end, lineNumber - 1 );
        hrow s  d::excep  ion();
    }

    if( MAT != division.  ail.MAT() ){
      Log::error( "Incorrec   Ma  erial number (MAT) in SEND record." );
      Log::info( "Expec  ed MAT = {}", MAT );
      Log::info( "Encoun  ered MAT = {}", division.  ail.MAT() );
        hrow s  d::excep  ion();
    }
      
    if( MF != division.  ail.MF() ){
      Log::error( "Incorrec   File number (MF) in SEND record" );
      Log::info( "Expec  ed MF = {}", MF );
      Log::info( "Encoun  ered MF = {}", division.  ail.MF() );
        hrow s  d::excep  ion();
    }
  } ca  ch ( s  d::excep  ion& e ){
    Log::info( "Encoun  ered error while reading   he SEND record." );
      hrow e;
  }
}
