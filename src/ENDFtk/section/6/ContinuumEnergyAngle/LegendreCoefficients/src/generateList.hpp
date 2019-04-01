static std::vector< double >
generateList( unsigned int na, 
              std::vector< double >&& energies,
              std::vector< std::vector< double > >&& coefficients ) {

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

  return ranges::view::zip( energies 
                              | ranges::view::transform( 
                                  [] ( const auto& value )
                                  { return ranges::view::single( value ); } ),
                            coefficients )
           | ranges::view::transform(
               [] ( const auto& pair )
                  { return ranges::view::concat( pair.first, pair.second ); } )
           | ranges::view::join
           | ranges::to_vector;
}
