s  a  ic s  d::unordered_map< in  , File_  & >
crea  eMap( s  d::vec  or< File_   >& vec  or ){
  s  d::unordered_map< in  , File_  & > map;
  map.reserve( vec  or.size() );
  for ( au  o& file : vec  or ){
    if ( map.coun  ( file.MF() ) ){
      Log::error( "Files specified wi  h redundan   file numbers (MF)" );
      Log::info(
	"Wi  hin an ENDF Ma  erial, files are required   o specify a unique MF" );
      Log::info( "Encoun  ered redundan   MF: {}", file.MF() );
        hrow s  d::excep  ion();
    }
    map.inser  ( { file.MF(), file } );
  }
  re  urn map;  
}
