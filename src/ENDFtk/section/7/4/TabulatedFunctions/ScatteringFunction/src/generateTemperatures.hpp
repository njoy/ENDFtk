static std::vector< ListRecord >
generateTemperatures( double beta,
                      std::vector< double >&& temperatures,
                      std::vector< long >&& li,
                      std::vector< std::vector< double > >&& s ) {
  unsigned int size = temperatures.size() - 1;
  std::vector< ListRecord > sequence;
  sequence.reserve( size );

  if ( ( size != li.size() ) || ( size + 1 != s.size() ) ) {

    Log::error( "Encountered inconsistent number of temperatures, "
                "interpolation flags and S(a,b) function values" );
    Log::info( "Number of LI values must be equal to NT - 1" );
    Log::info( "Number of S(a,b) sets must be equal to NT" );
    Log::info( "Number of LI values: {}", li.size() );
    Log::info( "Number of S(a,b) sets: {}", s.size() );
    Log::info( "NT value: {}", size + 1 );
    throw std::exception();
  }

  unsigned int i = 0;
  while( i++ < size ){
    sequence.emplace_back( ListRecord( temperatures[i], beta, li[i-1], 0, 0,
                                       std::move( s[i] ) ) );
  }

  return sequence;
}
