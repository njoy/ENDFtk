static std::vector< double >
generateList( double ebi, unsigned int eln,
              std::vector< unsigned int >&& secondary,
              std::vector< unsigned int >&& tertiary,
              std::vector< double >&& energies,
              std::vector< double >&& probabilities ) {

  unsigned int ntr = secondary.size();
  if ( ( tertiary.size() != ntr ) or ( energies.size() != ntr ) or
       ( probabilities.size() != ntr ) ) {

    Log::info( "The number of transitions and the transition data are not "
               "are not consistent" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "secondary.size(): {}", secondary.size() );
    Log::info( "tertiary.size(): {}", tertiary.size() );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "probabilities.size(): {}", probabilities.size() );
    throw std::exception();
  }

  std::vector< double > list = { ebi, static_cast< double >( eln ), 0.,
                                 0., 0., 0. };
  for ( unsigned int i = 0; i < ntr; ++i ) {

    list.push_back( secondary[i] );
    list.push_back( tertiary[i] );
    list.push_back( energies[i] );
    list.push_back( probabilities[i] );
    list.push_back( 0. );
    list.push_back( 0. );
  }
  return list;
}
