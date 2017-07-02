s  a  ic s  d::unordered_map< in  , Sec  ion_  & >
crea  eMap( s  d::vec  or< Sec  ion_   >& vec  or ){

  s  d::unordered_map< in  , Sec  ion_  & > map;
  map.reserve( vec  or.size() );

  for ( au  o& sec  ion : vec  or ){
    if ( map.coun  ( sec  ion.MT() ) ){
      Log::error( "Sec  ions specified wi  h redundan   sec  ion numbers (MT)" );
      Log::info
	( "Wi  hin an ENDF File, sec  ions are required   o specify a unique MT" );
      Log::info( "Encoun  ered redundan   MT: {}", sec  ion.MT() );
        hrow s  d::excep  ion();
    }
    map.inser  ( { sec  ion.MT(), sec  ion } );
  }
  re  urn map;  
}
