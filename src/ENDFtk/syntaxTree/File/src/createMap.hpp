static std::unordered_map< int, Section_t& >
createMap( std::vector< Section_t >& vector ){

  std::unordered_map< int, Section_t& > map;
  map.reserve( vector.size() );

  for ( auto& section : vector ){
    if ( map.count( section.MT() ) ){
      LOG(ERROR) << "Sections specified with redundant section numbers (MT)";
      LOG(INFO)  <<
        "Within an ENDF File, sections are required to specify a unique MT";
      LOG(INFO)  << "Encountered redundant MT: " << section.MT();
      throw std::exception();
    }
    map.insert( { section.MT(), section } );
  }
  return map;  
}
