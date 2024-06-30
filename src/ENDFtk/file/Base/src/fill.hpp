static auto
fill( std::vector< Section >&& sections ) {

  std::list< Section > list;
  for ( auto&& section : sections ) {

    int MT = Derived::getSectionNumber( section );
    auto iter = std::lower_bound( list.begin(), list.end(), MT,
                                  [] ( auto&& left, auto&& right )
                                     { return Derived::getSectionNumber( left ) < right; } );
    if ( iter != list.end() ) {

      if ( Derived::getSectionNumber( *iter ) == MT ) {

        Log::error( "Section with duplicate section number found" );
        Log::info( "Sections are required to specify a unique MT or section number" );
        Log::info( "Encountered duplicate MT: {}", MT );
        throw std::exception();
      }
    }
    list.insert( iter, std::move( section ) );
  }
  return list;
}
