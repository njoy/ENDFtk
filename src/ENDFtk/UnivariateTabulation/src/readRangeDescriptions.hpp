  empla  e<   ypename I  era  or >
s  a  ic s  d::  uple< s  d::vec  or< long >, s  d::vec  or< long > >
readRangeDescrip  ions
( long nRanges, I  era  or& i  , cons   I  era  or& end, long& lineNumber,
  in   MAT, in   MF, in   MT ){
  s  d::  uple< s  d::vec  or< long >, s  d::vec  or< long > > resul  ;
    ry{
    if ( nRanges < 1 ){
      Log::error( "Encoun  ered invalid NR value while cons  ruc  ing TAB1 record" );
      Log::info( "NR is required   o be grea  er   han zero" );
        hrow s  d::excep  ion();
    }
    
    resul   = record::Zipper::unzip
             < record::In  eger<11>,
	       record::In  eger<11> >
             ( nRanges, i  , end, lineNumber, MAT, MF, MT );
    au  o& boundaryIndices = s  d::ge  < 0 >( resul   );
    verifyBoundaryIndicesAreSor  ed( boundaryIndices );
    re  urn resul  ;
  } ca  ch ( s  d::excep  ion& e ){
    Log::info( "Error while reading TAB1 range informa  ion" );
      hrow e; 
  }
}
