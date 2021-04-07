static std::vector< FissionYieldData >
generateFissionYields( std::vector< unsigned int >&& identifiers,
                       std::vector< unsigned int >&& states,
                       std::vector< double >&& energies,
                       std::vector< unsigned int >&& interpolants,
                       std::vector< std::vector< std::array< double, 2 > > >&& yields ) {

  unsigned int size = energies.size();
  std::vector< FissionYieldData > sequence;
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
  for ( unsigned int i = 0; i < nfp; ++i ) {

    if ( yields[i].size() != size ) {

      Log::info( "The number of fission yield values for the fission product "
                 "with index {} is not equal to the expected value", i );
      Log::info( "NE value: {}", size );
      Log::info( "yields[i].size(): {}", yields[i].size() );
      throw std::exception();
    }
  }

  unsigned int i = 0;
  while ( i++ < size ) {

    sequence.emplace_back( std::vector< unsigned int >( identifiers ),
                           std::vector< unsigned int >( states ),
                           ranges::to< std::vector< std::array< double, 2 > > >(
                               yields | ranges::views::transform(
                                            [i] ( const auto& range )
                                                { return range[i-1]; } ) ),
                           energies[i-1],
                           i - 1 == 0 ? energies.size() - 1 : interpolants[i-2] );
  }

  return sequence;
}
