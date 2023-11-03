static std::vector< double >
generateList( std::vector< double >&& spins,
              std::vector< double >&& d,
              std::vector< double >&& gno,
              std::vector< double >&& gg,
              std::vector< double >&& gf,
              std::vector< double >&& gx ) {

  std::vector< double > list;
  unsigned int njs = spins.size();
  if ( ( d.size() != njs ) or ( gno.size() != njs ) or ( gg.size() != njs ) or
       ( gf.size() != njs ) or ( gx.size() != njs ) ) {

    Log::info( "The number of spin values and the resonance parameters are not "
               "consistent" );
    Log::info( "NJS value: {}", njs );
    Log::info( "spins.size(): {}", spins.size() );
    Log::info( "d.size(): {}", d.size() );
    Log::info( "gno.size(): {}", gno.size() );
    Log::info( "gg.size(): {}", gg.size() );
    Log::info( "gf.size(): {}", gf.size() );
    Log::info( "gx.size(): {}", gx.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < njs; ++i ) {

    list.push_back( d[i] );
    list.push_back( spins[i] );
    list.push_back( gno[i] );
    list.push_back( gg[i] );
    list.push_back( gf[i] );
    list.push_back( gx[i] );
  }
  return list;
}
