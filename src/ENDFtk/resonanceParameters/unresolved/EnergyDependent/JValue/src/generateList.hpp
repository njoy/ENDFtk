static std::vector< double >
generateList( int amux, int amun, int amug, int amuf,
              std::vector< double >&& energies,
              std::vector< double >&& d,
              std::vector< double >&& gx,
              std::vector< double >&& gn,
              std::vector< double >&& gg,
              std::vector< double >&& gf ) {

  std::vector< double > list{ 0.0, 0.0,
                              static_cast< double >( amux ),
                              static_cast< double >( amun ),
                              static_cast< double >( amug ),
                              static_cast< double >( amuf ) };

  unsigned int ne = energies.size();
  if ( ( d.size() != ne ) or ( gx.size() != ne ) or
       ( gn.size() != ne ) or ( gg.size() != ne ) or ( gf.size() != ne ) ) {

    Log::info( "The number of energies and the resonance parameters are not "
               "consistent" );
    Log::info( "NE value: {}", ne );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "d.size(): {}", d.size() );
    Log::info( "gx.size(): {}", gx.size() );
    Log::info( "gn.size(): {}", gn.size() );
    Log::info( "gg.size(): {}", gg.size() );
    Log::info( "gf.size(): {}", gf.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < ne; ++i ) {

    list.push_back( energies[i] );
    list.push_back( d[i] );
    list.push_back( gx[i] );
    list.push_back( gn[i] );
    list.push_back( gg[i] );
    list.push_back( gf[i] );
  }
  return list;
}
