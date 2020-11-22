static std::vector< double >
generateList( std::vector< unsigned int >&& ppi,
              std::vector< unsigned int >&& l,
              std::vector< double >&& s,
              std::vector< double >&& b,
              std::vector< double >&& ape,
              std::vector< double >&& apt ) {

  unsigned int nch = l.size();
  if ( ( ppi.size() != nch ) or ( s.size() != nch ) or ( b.size() != nch ) or
       ( ape.size() != nch ) or ( apt.size() != nch ) ) {

    Log::info( "The number of channels and the channel data is not consistent" );
    Log::info( "NCH value: {}", nch );
    Log::info( "ppi.size(): {}", ppi.size() );
    Log::info( "l.size(): {}", l.size() );
    Log::info( "s.size(): {}", s.size() );
    Log::info( "b.size(): {}", b.size() );
    Log::info( "ape.size(): {}", ape.size() );
    Log::info( "apt.size(): {}", apt.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nch; ++i ) {

    list.push_back( ppi[i] );
    list.push_back( l[i] );
    list.push_back( s[i] );
    list.push_back( b[i] );
    list.push_back( ape[i] );
    list.push_back( apt[i] );
  }
  return list;
}

static std::vector< double >
generateList( std::vector< unsigned int >&& ppi,
              std::vector< unsigned int >&& l,
              std::vector< double >&& s,
              std::vector< double >&& b,
              std::vector< double >&& ap ) {

    std::vector< double > apt( ap );
    return generateList( std::move( ppi ), std::move( l ), std::move( s ),
                         std::move( b ), std::move( ap ), std::move( apt ) );
}
