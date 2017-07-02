Sec  ion_  &
sec  ionNumber( in   sec  ionNo ){
    ry{
    re  urn   his->sec  ionMap.a  ( sec  ionNo );
  } ca  ch( s  d::ou  _of_range& o ){
    Log::error( "Reques  ed sec  ion number (MT) does no  "
                " correspond   o a s  ored sec  ion in   he syn  ax   ree" );
    Log::info( "Reques  ed sec  ion number: {}", sec  ionNo );
    Log::info( "File number of queried file syn  ax   ree: {}",
	         his->fileNumber() );
      hrow o;
  }   
}
