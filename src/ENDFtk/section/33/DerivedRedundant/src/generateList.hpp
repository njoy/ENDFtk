static std::vector< double >
generateList( std::vector< double >&& coefficients,
              std::vector< double >&& reactions ) {

  if ( coefficients.size() != reactions.size() ) {

    Log::error( "The number of coefficients and reactions are not consistent" );
    Log::info( "coefficients.size(): {}", coefficients.size() );
    Log::info( "reactions.size(): {}", reactions.size() );
    throw std::exception();
  }

  std::vector< double > list;

  for ( unsigned int i = 0; i < coefficients.size(); ++i ) {

    list.push_back( coefficients[i] );
    list.push_back( reactions[i] );
  }

  return list;
}
