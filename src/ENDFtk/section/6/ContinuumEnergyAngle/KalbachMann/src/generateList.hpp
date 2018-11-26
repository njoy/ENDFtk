template < typename Array >
static std::vector< double >
generateList( std::vector< Array >&& data ) {

  std::vector< double > list;
  for ( auto& entry : data ) { 

    list.insert( list.end(), entry.begin(), entry.end() );
  }
  return list;
}

