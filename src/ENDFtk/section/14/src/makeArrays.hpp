static std::vector< std::array< double, 2 > >
makeArrays( std::vector< double >&& energies,
            std::vector< double >&& levels ) {

  std::vector< std::array< double, 2 > > sequence;
  unsigned int size = energies.size();
  sequence.reserve( size );

  if ( size != levels.size() ) {

    Log::error( "Encountered inconsistent number of photon energy values and "
                "level energy values" );
    Log::info( "Number of photon energy values: {}", size );
    Log::info( "Number of energy level values: {}", levels.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < size; ++i ) {

    sequence.push_back( {{ energies[i], levels[i] }} );
  }

  return sequence;
}
