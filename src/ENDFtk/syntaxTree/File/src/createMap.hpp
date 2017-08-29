static tsl::hopscotch_map< int, const Section_t* >
createMap( const std::vector< Section_t >& vector ){ 
  tsl::hopscotch_map< int, const Section_t* > map;
  map.reserve( vector.size() );

  for ( auto& section : vector ){
    if ( map.count( section.MT() ) ){
      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
      ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", section.MT() );
      throw std::exception();
    }
    map.insert( { section.MT(), &section } );
  }
  return map;  
}
