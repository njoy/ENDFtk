static std::vector< ListRecord >
generateTemperatures( std::vector< double >&& temperatures,
                      std::vector< long >&& li,
                      std::vector< std::vector< double > >&& s ) {
  unsigned int size = temperatures.size() - 1;
  std::vector< ListRecord > sequence;
  sequence.reserve( size );

  if ( size + 1 != s.size() ) {

    Log::error( "Inconsistent number of temperatures and S(E,T) functions" );
    Log::info( "The number of temperatures must be equal to the number of "
               "S(E,T) functions" );
    Log::info( "Number of temperatures: {}", size + 1 );
    Log::info( "Number of S(E,T) functions: {}", s.size() );
    throw std::exception();
  }

  unsigned int i = 0;
  while( i++ < size ){
    sequence.emplace_back( ListRecord( temperatures[i], 0, li[i-1], 0, 0,
                                       std::move( s[i] ) ) );
  }

  return sequence;
}
