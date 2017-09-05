static tsl::hopscotch_map< int, const Section* >
collectMap( const std::vector< Section >& sectionVector ){
  tsl::hopscotch_map< int, const Section* > sectionMap;
  sectionMap.reserve( sectionVector.size() );
  for ( const Section& section : sectionVector ){
    if( sectionMap.count( section.MT() ) ){
      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
      ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", section.MT() );
      throw std::exception();
    }
    sectionMap.insert( { section.MT(), &section } );
  }
  return sectionMap;
}
