template < typename Array >
static std::vector< double >
generateList( std::vector< Array >&& data ) {

  std::vector< double > list;
  for ( auto&& array : data ) {

    list.insert( list.end(), array.begin(), array.end() );
  }

  return list;
}
