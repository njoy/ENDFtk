static auto
fill( std::vector< FileVariant >&& files ) {

  std::list< FileVariant > list;
  for ( auto&& file : files ) {

    auto getMF = [] ( auto&& value ) { return value.MF(); };
    int MF = std::visit( getMF, file );
    auto iter = std::lower_bound( list.begin(), list.end(), MF,
                                  [&getMF] ( auto&& left, auto&& right )
                                           { return std::visit( getMF, left ) < right; } );
    if ( iter != list.end() ) {

      if ( std::visit( getMF, *iter ) == MF ) {

        Log::error( "File with duplicate file number found" );
        Log::info( "Files are required to specify a unique MF or file number" );
        Log::info( "Encountered duplicate MF: {}", MF );
        throw std::exception();
      }
    }
    list.insert( iter, std::move( file ) );
  }
  return list;
}
