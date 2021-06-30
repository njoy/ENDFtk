static std::vector< FissionYieldData >
generateFissionYields( std::vector< unsigned int >&& identifiers,
                       std::vector< unsigned int >&& states,
                       std::vector< double >&& energies,
                       std::vector< unsigned int >&& interpolants,
                       std::vector< std::vector< std::array< double, 2 > > >&& yields ) {

  std::vector< FissionYieldData > sequence;
  unsigned int size = energies.size();
  sequence.reserve( size );

  if ( size != interpolants.size() + 1 ) {

    Log::error( "Encountered inconsistent number of energy values and "
                "interpolation flags" );
    Log::info( "Number of I values must be equal to NE - 1" );
    Log::info( "Number of I values: {}", interpolants.size() );
    Log::info( "NE value: {}", size );
    throw std::exception();
  }

  unsigned int nfp = identifiers.size();
  if ( ( nfp != states.size() ) || ( nfp != yields.size() ) ) {

    Log::error( "Encountered inconsistent number of identifiers, isomeric states "
                "and yield data" );
    Log::info( "Number of identifiers, isomeric states and yield sets must be the same" );
    Log::info( "Number of identifiers: {}", identifiers.size() );
    Log::info( "Number of isomeric states: {}", states.size() );
    Log::info( "Number of yield sets: {}", yields.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < nfp; ++i ) {

    if ( yields[i].size() != size ) {

      Log::error( "The number of fission yield values for the fission product "
                 "with index {} is not equal to the expected value", i );
      Log::info( "NE value: {}", size );
      Log::info( "yields[i].size(): {}", yields[i].size() );
      throw std::exception();
    }
  }

  for ( unsigned int i = 0; i < size; ++i ) {

    sequence.emplace_back( std::vector< unsigned int >( identifiers ),
                           std::vector< unsigned int >( states ),
                           ranges::to< std::vector< std::array< double, 2 > > >(
                               yields | ranges::view::transform(
                                            [i] ( const auto& range )
                                                { return range[i]; } ) ),
                           energies[i],
                           i == 0 ? energies.size() - 1 : interpolants[i-1] );
  }

  return sequence;
}
