static std::vector< double >
generateList( std::vector< unsigned int >&& identifiers,
              std::vector< unsigned int >&& states,
              std::vector< double >&& abundances,
              std::vector< double >&& weights,
              std::vector< double >&& xs ) {

  unsigned int ni = identifiers.size();
  if ( ( states.size() != ni ) or ( abundances.size() != ni ) or
       ( weights.size() != ni ) or ( xs.size() != ni ) ) {

    Log::info( "The number of isotopes and the eleemnt information data "
               "are not consistent" );
    Log::info( "ni value: {}", ni );
    Log::info( "identifiers.size(): {}", identifiers.size() );
    Log::info( "states.size(): {}", states.size() );
    Log::info( "abundances.size(): {}", abundances.size() );
    Log::info( "weights.size(): {}", weights.size() );
    Log::info( "xs.size(): {}", xs.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < ni; ++i ) {

    list.push_back( identifiers[i] );
    list.push_back( states[i] );
    list.push_back( abundances[i] );
    list.push_back( weights[i] );
    list.push_back( xs[i] );
    list.push_back( 0. );
  }
  return list;
}
