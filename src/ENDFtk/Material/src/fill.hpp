static auto
fill( std::vector< FileVariant >&& files ) {

  std::map< int, FileVariant > map;
  for ( auto&& file : files ) {

    int MF = std::visit( [] ( auto&& value ) { return value.MF(); }, file );
    if ( not map.emplace( MF, std::move( file ) ).second ) {

      Log::error( "File with duplicate file number found" );
      Log::info( "Files are required to specify a unique MF or file number" );
      Log::info( "Encountered duplicate MF: {}", MF );
      throw std::exception();
    }
  }
  return map;
}
