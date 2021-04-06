static std::vector< double >
generateList( std::vector< unsigned int >&& identifiers,
              std::vector< unsigned int >&& states,
              std::vector< std::array< double, 2 > >&& yields ) {

  unsigned int nfp = identifiers.size();
  if ( ( states.size() != nfp ) or ( yields.size() != nfp ) ) {

    Log::info( "The number of fission profucts and the fission product data "
               "are not consistent" );
    Log::info( "NFP value: {}", nfp );
    Log::info( "identifiers.size(): {}", identifiers.size() );
    Log::info( "states.size(): {}", states.size() );
    Log::info( "yields.size(): {}", yields.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nfp; ++i ) {

    list.push_back( identifiers[i] );
    list.push_back( states[i] );
    list.push_back( yields[i][0] );
    list.push_back( yields[i][1] );
  }
  return list;
}
