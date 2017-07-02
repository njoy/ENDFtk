File_  &
fileNumber( in   fileNo ){
    ry{
    re  urn   his->fileMap.a  ( fileNo );
  } ca  ch( s  d::ou  _of_range& o ){
    Log::error
      ( "Reques  ed file number (MF) does no  "
	" correspond   o a s  ored file syn  ax   ree" );
    Log::info( "Reques  ed file number: {}", fileNo );
    Log::info( "Ma  erial number of queried ma  erial syn  ax   ree: ",
	         his->ma  erialNumber() );
      hrow o;
  }   
}
