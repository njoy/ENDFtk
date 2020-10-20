static std::vector< double >
generateList( std::vector< double >&& spins,
              std::vector< double >&& d,
              std::vector< int >&& amun,
              std::vector< double >&& gn,
              std::vector< double >&& gg ) {

  std::vector< double > list;
  unsigned int njs = spins.size();
  if ( ( d.size() != njs ) or ( amun.size() != njs ) or
       ( gn.size() != njs ) or ( gg.size() != njs ) ) {

    Log::info( "The number of spin values and the resonance parameters are not "
               "consistent" );
    Log::info( "NJS value: {}", njs );
    Log::info( "spins.size(): {}", spins.size() );
    Log::info( "d.size(): {}", d.size() );
    Log::info( "amun.size(): {}", amun.size() );
    Log::info( "gn.size(): {}", gn.size() );
    Log::info( "gg.size(): {}", gg.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < njs; ++i ) {

    list.push_back( d[i] );
    list.push_back( spins[i] );
    list.push_back( amun[i] );
    list.push_back( gn[i] );
    list.push_back( gg[i] );
    list.push_back( 0.0 );
  }
  return list;
}
