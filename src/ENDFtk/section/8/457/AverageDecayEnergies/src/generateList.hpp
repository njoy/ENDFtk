static std::vector< double >
generateList( std::vector< std::array< double, 2 > >&& energies ) {

  std::vector< double > list;
  list.reserve( energies.size() * 2 );
  for ( auto&& entry : energies ) {

    list.push_back( entry[0] );
    list.push_back( entry[1] );
  }
  return list;
}
