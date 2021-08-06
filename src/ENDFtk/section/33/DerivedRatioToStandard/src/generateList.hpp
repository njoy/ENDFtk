static std::vector< double >
generateList( double XMFS, double XLFSS,
              std::vector< double >&& energies,
              std::vector< double >&& weights ) {

  if ( energies.size() != weights.size() ) {

    Log::error( "The number of energies and weights are not consistent" );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "weights.size(): {}", weights.size() );
    throw std::exception();
  }

  std::vector< double > list = { XMFS, XLFSS };

  for ( unsigned int i = 0; i < energies.size(); ++i ) {

    list.push_back( energies[i] );
    list.push_back( weights[i] );
  }

  return list;
}
