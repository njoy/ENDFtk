Base( cons   HEAD& head, in   MAT, in   MF ) :
  sec  ionNo( head.MT() ), 
  ZA_( head.ZA() ), 
  a  omicWeigh  Ra  io_( head.a  omicWeigh  Ra  io() ) { 
  if( MAT != head.MAT() ){
    Log::error( "Incorrec   Ma  erial number (MAT)." );
    Log::info( "Expec  ed MAT = {}", MAT );
    Log::info( "Encoun  ered MAT = {}", head.MAT() );
      hrow s  d::excep  ion();
  }
  if( MF != head.MF() ){
    Log::error( "Incorrec   File number (MF)." );
    Log::info( "Expec  ed MF = {}", MF );
    Log::info( "Encoun  ered MF = {}", head.MF() );
      hrow s  d::excep  ion();
  }
}
