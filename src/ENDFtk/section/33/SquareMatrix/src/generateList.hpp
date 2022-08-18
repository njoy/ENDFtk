static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& values ) {

  std::vector< double > list;
  list.insert( list.end(), energies.begin(), energies.end() );
  list.insert( list.end(), values.begin(), values.end() );
  return list;
}
