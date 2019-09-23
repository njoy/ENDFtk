static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& probabilities ) {

  unsigned int NT = energies.size();
  if ( energies.size() != probabilities.size() ) {

    Log::error( "The number of energy and probability values must be the same" );
    Log::info( "energies.size(): {}", NT );
    Log::info( "probabilities.size(): {}", probabilities.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < NT; ++i ) {

    list.push_back( energies[i] );
    list.push_back( probabilities[i] );
  }
  return list;
}

static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& probabilities,
              std::vector< double >&& conditionalProbabilities ) {

  unsigned int NT = energies.size();
  if ( ( energies.size() != probabilities.size() ) or
       ( energies.size() != conditionalProbabilities.size() ) ) {

    Log::error( "The number of energy and probability values must be the same" );
    Log::info( "energies.size(): {}", NT );
    Log::info( "probabilities.size(): {}", probabilities.size() );
    Log::info( "conditionalProbabilities.size(): {}",
               conditionalProbabilities.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < NT; ++i ) {

    list.push_back( energies[i] );
    list.push_back( probabilities[i] );
    list.push_back( conditionalProbabilities[i] );
  }
  return list;
}
