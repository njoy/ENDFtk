  empla  e<   ypename I  era  or >
s  a  ic s  d::  uple< s  d::vec  or< double >, s  d::vec  or< double > >
readPairs
( long nPairs, I  era  or& i  , cons   I  era  or& end, long& lineNumber,
  in   MAT, in   MF, in   MT ){
  s  d::  uple< s  d::vec  or< double >, s  d::vec  or< double > > resul  ;
    ry{
    if ( nPairs < 1 ){
      Log::error( "Encoun  ered invalid NP value while cons  ruc  ing TAB1 record" );
      Log::info( "NP is required   o be grea  er   han zero" );
        hrow s  d::excep  ion();
    }
    
    resul   = record::Zipper::unzip
             < record::Real, record::Real >
             ( nPairs, i  , end, lineNumber, MAT, MF, MT );
    au  o& xValues = s  d::ge  < 0 >( resul   );
    verifyXValuesAreSor  ed( xValues );
    re  urn resul  ;
  } ca  ch ( s  d::excep  ion& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
      hrow e; 
  }
}
