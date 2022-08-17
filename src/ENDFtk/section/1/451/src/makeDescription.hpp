static
std::vector< TextRecord >
makeDescription( const std::string& description ) {

  std::vector< TextRecord > text;
  std::istringstream in( description );
  std::string line;

  while ( std::getline( in, line, '\n' ) ) {

    text.emplace_back( std::move( line ) );
  }

  return text;
}
