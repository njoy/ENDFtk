static std::vector< double >
generateList( unsigned int na,
              std::vector< double >&& energies,
              std::vector< double >&& totalEmissionProbabilities,
              std::vector< std::vector< double > >&& cosines,
              std::vector< std::vector< double > >&& probabilities ) {

  if ( ( energies.size() != totalEmissionProbabilities.size() ) ||
       ( energies.size() != cosines.size() ) ||
       ( energies.size() != probabilities.size() ) ) {

    Log::error( "A total emission probability value f0 and a set of cosines "
                "and probabilities must be given for each energy value" );
    Log::info( "Expected size: {}", energies.size() );
    Log::info( "Found f0 values: {}", totalEmissionProbabilities.size() );
    Log::info( "Found cosine sets: {}", cosines.size() );
    Log::info( "Found probability sets: {}", probabilities.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < energies.size(); ++i ) {

    verifySorted( cosines[i], "Energy" );

    if ( ( cosines[i].size() != probabilities[i].size() ) ||
         ( cosines[i].size() != na / 2 ) ) {

      Log::error( "The number of cosines and probabilities for each energy "
                  "value must be the same and equal to na/2" );
      Log::info( "Expected: {}", na / 2 );
      Log::info( "Found cosines: {}", cosines[i].size() );
      Log::info( "Found probabilities: {}", probabilities[i].size() );
      Log::info( "Energy: {}", energies[i] );
      throw std::exception();
    }

    list.push_back( energies[i] );
    list.push_back( totalEmissionProbabilities[i] );
    for ( unsigned int j = 0; j < cosines[i].size(); ++j ) {

      list.push_back( cosines[i][j] );
      list.push_back( probabilities[i][j] );
    }
  }
  return list;
}
