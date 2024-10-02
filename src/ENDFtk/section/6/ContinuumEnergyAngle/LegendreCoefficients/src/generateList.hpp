static std::vector< double >
generateList( unsigned int na,
              std::vector< double >&& energies,
              std::vector< std::vector< double > >&& coefficients ) {

  std::vector< double > list;
  list.reserve( energies.size() * ( 2 + na ) );

  if ( energies.size() != coefficients.size() ) {

    Log::error( "The number of energies and number of sets if coefficients "
                "must be the same" );
    Log::info( "Number of energies: {}", energies.size() );
    Log::info( "Number of coefficient sets: {}", coefficients.size() );
    throw std::exception();
  }

  for ( auto& entry : coefficients ) {

    if ( 1 + na != entry.size() ) {

      Log::error( "The number of coefficients for each energy value must "
                  "be the same" );
      Log::info( "Expected: {}", 1 + na );
      Log::info( "Found: {}", entry.size() );
      throw std::exception();
    }
  }

  for ( unsigned int i = 0; i < energies.size(); ++i ) {

    list.push_back( energies[i] );
    list.insert( list.end(), coefficients[i].begin(), coefficients[i].end() );
  }

  return list;
}
