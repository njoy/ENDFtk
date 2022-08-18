static std::vector< double >
generateList( std::vector< std::array< double, 2 > >&& energies ) {

  std::vector< double > list;
  for ( const auto& energy : energies ) {

    list.insert( list.end(), energy.begin(), energy.end() );
  }
  return list;
}
