static std::vector< double >
generateList( std::vector< std::tuple< double, double > >&& energies ) {

  std::vector< double > list;
  for ( unsigned int i = 0; i < energies.size(); ++i ) {

    list.push_back( std::get< 0 >( energies[i] ) );
    list.push_back( std::get< 1 >( energies[i] ) );
  }
  return list;
}
