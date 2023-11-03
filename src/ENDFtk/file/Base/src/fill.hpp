static auto
fill( std::vector< Section >&& sections ) {

  std::map< int, Section > map;
  for ( auto&& section : sections ) {

    int MT = Derived::getSectionNumber( section );
    if ( not map.emplace( MT, std::move( section ) ).second ) {

      Log::error( "Section with duplicate section number found" );
      Log::info( "Sections are required to specify a unique MT or section number" );
      Log::info( "Encountered duplicate MT: {}", MT );
      throw std::exception();
    }
  }
  return map;
}
