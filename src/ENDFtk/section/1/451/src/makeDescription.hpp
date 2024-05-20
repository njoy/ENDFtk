static
std::vector< TextRecord >
makeDescription( const std::string& description ) {

  std::vector< TextRecord > result;
  auto begin = description.begin();
  auto iter = std::find_if( begin, description.end(),
                            [] ( auto&& character ) { return character == '\n'; } );
  while ( begin != description.end() ) {

    result.emplace_back( std::string( begin, iter ) );
    begin = iter + 1;
    iter = std::find_if( begin, description.end(),
                         [] ( auto&& character ) { return character == '\n'; } );
  }
  return result;
}
