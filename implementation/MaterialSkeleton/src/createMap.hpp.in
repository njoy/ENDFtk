static std::unordered_map< int, FileSkeleton_t& >
createMap( std::vector< FileSkeleton_t >& vector ){
  std::unordered_map< int, FileSkeleton_t& > map;
  map.reserve( vector.size() );
  for ( auto& file : vector ){
    if ( map.count( file.MF() ) ){
      LOG(ERROR) << "Files specified with redundant file numbers (MF)";
      LOG(INFO)  <<
        "Within an ENDF Material, files are required to specify a unique MF";
      LOG(INFO)  << "Encountered redundant MF: " << file.MF();
      throw std::exception();
    }
    map.insert( { file.MF(), file } );
  }
  return map;  
}
