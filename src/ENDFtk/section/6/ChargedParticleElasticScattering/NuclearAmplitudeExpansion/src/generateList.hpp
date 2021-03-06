static std::vector< double >
generateList( unsigned int NL,
              std::vector< double >&& b,
              std::vector< double >&& ar,
              std::vector< double >&& ai ) {

  if ( ar.size() != NL + 1 ) {

    Log::info( "The number of real values for a must be equal to NL + 1" );
    Log::info( "NL value: {}", NL );
    Log::info( "ar.size(): {}", ar.size() );
    throw std::exception();
  }
  if ( ai.size() != NL + 1 ) {

    Log::info( "The number of imaginary values for a must be equal to NL + 1" );
    Log::info( "NL value: {}", NL );
    Log::info( "ai.size(): {}", ai.size() );
    throw std::exception();
  }
  if ( not ( ( b.size() == NL + 1 ) or ( b.size() == 2 * NL + 1 ) ) ) {

    Log::info( "The number of b values must be equal to NL + 1 of 2*NL + 1 "
               "for nuclear amplitude expansion" );
    Log::info( "NL value: {}", NL );
    Log::info( "b.size(): {}", b.size() );
    throw std::exception();
  }

  std::vector< double > list( b );
  for ( unsigned int i = 0; i < NL + 1; ++i ) {

    list.push_back( ar[i] );
    list.push_back( ai[i] );
  }
  return list;
}

static std::vector< double >
generateList( unsigned int NL,
              std::vector< double >&& b,
              std::vector< std::complex< double > >&& a ) {

  if ( a.size() != NL + 1 ) {

    Log::info( "The number of values for a must be equal to NL + 1" );
    Log::info( "NL value: {}", NL );
    Log::info( "a.size(): {}", a.size() );
    throw std::exception();
  }
  if ( ! ( ( b.size() == NL + 1 ) or ( b.size() == 2 * NL + 1 ) ) ) {

    Log::info( "The number of b values must be equal to NL + 1 of 2*NL + 1 "
               "for nuclear amplitude expansion" );
    Log::info( "NL value: {}", NL );
    Log::info( "b.size(): {}", b.size() );
    throw std::exception();
  }

  std::vector< double > list( b );
  for ( const auto& value : a ) {

    list.push_back( value.real() );
    list.push_back( value.imag() );
  }
  return list;
}
