static std::map< int, Section >
fill( std::vector< Section >&& sections ) {

  std::map< int, Section > sectionMap;

  auto verifyAndInsert = [&] ( auto&& section ) {

    if ( sectionMap.count( section.MT() ) ) {

      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
      ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", section.MT() );
      throw std::exception();
    }
    sectionMap.insert( { section.MT(), std::move( section ) } );
  };

  ranges::for_each( sections, verifyAndInsert );
  return sectionMap;
}
