static std::vector< double >
generateList( std::vector< double >&& constants,
              std::vector< double >&& abundances ) {

  auto nnf = constants.size();
  if ( nnf == 0 ) {

    Log::error( "The number of precursor families NNF cannot be zero" );
    throw std::exception();
  }
  if ( nnf != abundances.size() ) {

    Log::error( "The number of precursors and number of abundance values is "
                "not consistent" );
    Log::info( "NNF value: {}", nnf );
    Log::info( "abundances.size(): {}", abundances.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nnf; ++i ) {

    list.push_back( constants[i] );
    list.push_back( abundances[i] );
  }
  return list;
}
