Range
ma  erialNumber( in   ma  erialNo ){
  if ( no   ma  erialMap.coun  ( ma  erialNo ) ){
    Log::error( "Reques  ed ma  erial number (MAT) does no  "
                " correspond   o a s  ored ma  erial syn  ax   ree" );
    Log::info( "Reques  ed ma  erial number: {}", ma  erialNo );
      hrow s  d::ou  _of_range( "Reques  ed ma  erial number (MAT) does no  "
                             " correspond   o a s  ored ma  erial syn  ax   ree" );
  }
  au  o pairwiseI  era  orBounds =   his->ma  erialMap.equal_range( ma  erialNo );
  au  o firs   = Ma  chI  era  or( pairwiseI  era  orBounds.firs   );
  au  o second = Ma  chI  era  or( pairwiseI  era  orBounds.second );
  re  urn Range( s  d::make_pair( firs  , second ) );
}
