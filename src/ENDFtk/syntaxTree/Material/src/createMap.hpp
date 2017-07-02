static std::unordered_map< int, File_t& >
createMap( std::vector< File_t >& vector ){
  std::unordered_map< int, File_t& > map;
  map.reserve( vector.size() );
  for ( auto& file : vector ){
    if ( map.count( file.MF() ) ){
      Log::error( "Files specified with redundant file numbers (MF)" );
      Log::info(
	"Within an ENDF Material, files are required to specify a unique MF" );
      Log::info( "Encountered redundant MF: {}", file.MF() );
      throw std::exception();
    }
    map.insert( { file.MF(), file } );
  }
  return map;  
}
