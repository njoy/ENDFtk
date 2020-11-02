struct insert {
  auto operator()( std::map< int, Section >& sectionMap,
                   Section&& section ) const {

    int MT = section.MT();
    if ( not sectionMap.emplace( MT, std::move( section ) ).second ) {

      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
      ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", section.MT() );
      throw std::exception();
    }
  }

  auto operator()( std::map< int, Section >& sectionMap,
                   Section& section ) const {

    return (*this)( sectionMap, std::move( section ) );
  }
};
