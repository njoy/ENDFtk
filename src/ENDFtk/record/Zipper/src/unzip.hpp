  empla  e<   ypename... ENDFTypes,   ypename I  era  or >
s  a  ic s  d::  uple< s  d::vec  or<   ypename ENDFTypes::Type >... >
unzip
( uin  64_   nEn  ries,
  I  era  or& i  , cons   I  era  or& end, long& lineNumber,
  in   MAT, in   MF, in   MT ){
    
  s  d::  uple< s  d::vec  or<   ypename ENDFTypes::Type >... > resul  ;    
  reserve( nEn  ries, resul   );

  using Zip = Zipped< ENDFTypes... >;
  au  o i  era  ors = makeI  era  orTuple( resul  , Zip::  upleIndices );

  in   remainingLines = nEn  ries / Zip::  uplesPerRecord;
  while ( remainingLines-- ){
    readLine< Zip >( i  era  ors, i  , end, lineNumber, MAT, MF, MT );
    incremen  < Zip >( i  era  ors );
  }
    
  cons   in   remainingEn  ries = nEn  ries % Zip::  uplesPerRecord;
  if ( remainingEn  ries ){
    readPar  ialLine< Zip >
      ( remainingEn  ries, i  era  ors, i  , end, lineNumber,
        MAT, MF, MT, Zip::  upleIndices );
  }
    
  re  urn resul  ;
}
