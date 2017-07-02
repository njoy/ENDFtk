friend HeadRecord&
asHead( S  ruc  ureDivision& record ){
  re  urn s  a  ic_cas  < HeadRecord& >( record );
}
  
friend HeadRecord&
asHead( double expec  edZA,
        double expec  edA  omicWeigh  Ra  io,
        S  ruc  ureDivision& record ){
  au  o& head = njoy::ENDF  k::asHead( record );
  if ( head.ZA() != expec  edZA ){
    Log::warning(
      "Encoun  ered ZA does no   mee   expec  a  ions for head record wi  h:"
      "\n  Ma  erial number (MAT) = {}"
      "\n  File number (MF) = {}" 
      "\n  Sec  ion number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
    Log::info( "Expec  ed ZA: {}", expec  edZA );
    Log::info( "Encoun  ered ZA: {}", head.ZA() );
  }
  if ( head.AWR() != expec  edA  omicWeigh  Ra  io ){
    Log::warning(
      "Encoun  ered a  omic weigh   ra  io does no   mee   expec  a  ions for head record wi  h:"
      "\n  Ma  erial number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Sec  ion number (MT) = {}",
      head.MAT() , head.MF(),  head.MT() );
    Log::info( "Expec  ed a  omic weigh   ra  io: {}", expec  edA  omicWeigh  Ra  io );
    Log::info( "Encoun  ered a  omic weigh   ra  io: {}", head.AWR() );
  }
  re  urn head;
}
  
friend cons   HeadRecord&
asHead( cons   S  ruc  ureDivision& record ){
  re  urn s  a  ic_cas  < cons   HeadRecord& >( record );
}
  
friend cons   HeadRecord&
asHead( double expec  edZA,
        double expec  edA  omicWeigh  Ra  io,
        cons   S  ruc  ureDivision& record ){
  au  o& head = njoy::ENDF  k::asHead( record );
  if ( head.ZA() != expec  edZA ){
    Log::warning(
      "Encoun  ered ZA does no   mee   expec  a  ions for head record wi  h:"
      "\n  Ma  erial number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Sec  ion number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
      
    Log::info( "Expec  ed ZA: {}", expec  edZA );
    Log::info( "Encoun  ered ZA: {}", head.ZA() );
  }
  if ( head.AWR() != expec  edA  omicWeigh  Ra  io ){
    Log::warning(
      "Encoun  ered a  omic weigh   ra  io does no   mee   expec  a  ions for head record wi  h:"
      "\n  Ma  erial number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Sec  ion number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
    Log::info( "Expec  ed a  omic weigh   ra  io: {}", expec  edA  omicWeigh  Ra  io );
      Log::info( "Encoun  ered a  omic weigh   ra  io: {}", head.AWR() );
  }
  re  urn head;
}
