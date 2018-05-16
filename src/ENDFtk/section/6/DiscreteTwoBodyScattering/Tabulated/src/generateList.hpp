static std::vector< double >
generateList( std::vector< double >&& cosines,
              std::vector< double >&& probabilities ) {

  unsigned int NL = cosines.size();
  if ( cosines.size() != probabilities.size() ) {

    Log::info( "The number of cosine and probability values must be the same" );
    Log::info( "cosines.size(): {}", NL );
    Log::info( "probabilities.size(): {}", probabilities.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < NL; ++i ) {

    list.push_back( cosines[i] );
    list.push_back( probabilities[i] );
  }
  return list;
}
